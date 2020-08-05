
#ifndef UI_UI_H_
#define UI_UI_H_
#include "../Window.h"

#include <stdio.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>

#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include "../Skybox.h"
#include "Slider.h"
#include "ColorPicker.h"
#include "ScrollPane.h"
#include "Checkbox.h"
#include "Label.h"
#include "VListLayout.h"



typedef bool(*windowcloselistener)(Window *target);
typedef Panel* (*builder)(xmlNode* n,std::string styleclass);
typedef void(*listfunction)(Panel *panel,void* data, int index);


namespace UI {
		std::string colstrings[12]={
			"background",	"foreground",	"border", 
			"hover-background", "hover-foreground",	"hover-border",
			"click-background", "click-foreground", "click-border"
			"select-background", "select-foreground", "select-border"
		};


		std::list<Window*> windows;
		unsigned int colors[16];
		std::map<std::string,void*> data;
		std::map<std::string, std::map<std::string,unsigned int*>   >rules;
		std::map<std::string,TTF_Font*> fonts;
		std::map<std::string,builder> factory ={
			{std::string("Window") , []( xmlNode *node,std::string styleclass){
					Window* win=new Window (
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"x")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"y")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"width")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"height")),
						"engine",
							
						(SDL_WINDOW_FULLSCREEN * ((bool)xmlHasProp( node,(const xmlChar*)"fullscreen"))  ) |
						(SDL_WINDOW_FULLSCREEN_DESKTOP * ((bool)xmlHasProp( node,(const xmlChar*)"fullscreen_desktop"))  ) |
						(SDL_WINDOW_HIDDEN * ((bool)xmlHasProp( node,(const xmlChar*)"hidden"))  ) |
						(SDL_WINDOW_BORDERLESS * ((bool)xmlHasProp( node,(const xmlChar*)"borderless"))  ) |
						(SDL_WINDOW_RESIZABLE * ((bool)xmlHasProp( node,(const xmlChar*)"resizable"))  ) |
						(SDL_WINDOW_MINIMIZED * ((bool)xmlHasProp( node,(const xmlChar*)"minimized"))  ) |
						(SDL_WINDOW_MAXIMIZED * ((bool)xmlHasProp( node,(const xmlChar*)"maximized"))  ) |
						(SDL_WINDOW_INPUT_GRABBED * ((bool)xmlHasProp( node,(const xmlChar*)"focused"))  ) 
					);
					
					if (xmlHasProp( node,(const xmlChar*)"onclose")){
						std::string key=(const char*)xmlGetProp( node,(const xmlChar*)"onclose");
					if (data.find(key) == data.end())
						data[key]=0;
							
							
						win->closelistener=  ((windowcloselistener) (data[key]));
					}
					return (Panel*)win;
					}
			},
			{std::string("Panel"), [](xmlNode *node,std::string styleclass){ 
				
				Panel* p=new Panel(
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"x")),
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"y")),
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"width")),
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"height")),
					0
				) ;
				return p;
			}},
			{std::string("Label"), [](xmlNode *node,std::string styleclass)  { 
				
				Label* label=new Label(
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"x")),
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"y")),
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"width")),
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"height")),
					0,
					(TTF_Font*) rules[styleclass]["font"],
					(const char*) xmlGetProp( node,(const xmlChar*)"text")
				) ;
				return (Panel*)label;
			}}
			,
			{std::string("Checkbox"), [](xmlNode *node,std::string styleclass){ 
				Checkbox* cb=new Checkbox(
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"x")),
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"y")),
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"size"))
				) ;
			
				if (xmlHasProp( node,(const xmlChar*)"bit")){
					cb->bitflag <<= atoi((const char*)xmlGetProp( node,(const xmlChar*)"bit"));
				}
				cb->state=(unsigned char*)data[std::string((const char*) xmlGetProp( node,(const xmlChar*)"value"))];	
				return (Panel*)cb;
			}},
			{std::string("Slider") , [](xmlNode *node,std::string styleclass){ 
				if (std::string( (const char*)xmlGetProp( node,(const xmlChar*)"type")  )=="float"){
					
					Slider<float>* slider=new Slider<float>(
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"x")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"y")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"width")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"height")),
						0
					) ;
					if (xmlHasProp( node,(const xmlChar*)"min")){
						slider->min=atof((const char*)xmlGetProp( node,(const xmlChar*)"min"));
					}
					if (xmlHasProp( node,(const xmlChar*)"max")){
						slider->max=atof((const char*)xmlGetProp( node,(const xmlChar*)"max"));
					}
					
					slider->value=(float*)data[std::string((const char*) xmlGetProp( node,(const xmlChar*)"value"))];
					return (Panel*)slider;
				}else if (
				std::string( (const char*)xmlGetProp( node,(const xmlChar*)"type")  )=="uint8"){
					Slider<unsigned char>* slider=new Slider<unsigned char>(
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"x")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"y")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"width")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"height")),
						0
					) ;
					
					if (xmlHasProp( node,(const xmlChar*)"min")){
						slider->min=atoi((const char*)xmlGetProp( node,(const xmlChar*)"min"));
					}
					if (xmlHasProp( node,(const xmlChar*)"max")){
						slider->max=atoi((const char*)xmlGetProp( node,(const xmlChar*)"max"));
					}
					
			
					slider->value=(unsigned char*)data[std::string((const char*) xmlGetProp( node,(const xmlChar*)"value"))];
					return (Panel*)slider;
				}
				
				
			return (Panel*) 0;
			}
			
			},
			{std::string("ScrollPane") , [](xmlNode* node,std::string styleclass){ 
				
				ScrollPane* scrollpane=new ScrollPane(
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"x")),
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"y")),
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"width")),
					atoi((const char*)xmlGetProp( node,(const xmlChar*)"height")),
					0
				) ;
				
				for (char i=0;i<12;i++){
					scrollpane->viewport->colors[i] = rules[styleclass][colstrings[i]] ;
					scrollpane->v_handle->colors[i] = rules[styleclass][colstrings[i]] ;
					scrollpane->content->colors[i] = rules[styleclass][colstrings[i]] ;
				
				}
				return (Panel*)scrollpane;
			}},{std::string("ColorPicker") , [](xmlNode* node,std::string styleclass){ 

				if (std::string( (const char*)xmlGetProp( node,(const xmlChar*)"type")  )=="uint8"){
					ColorPicker<unsigned char>* cp=new ColorPicker<unsigned char>(
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"x")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"y")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"width")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"height")),
						0
					) ;
					
					
					for (char i=0;i<12;i++){
						cp->colorBall->colors[i] = rules[styleclass][colstrings[i]] ;
						cp->brightnessPicker->colors[i] = rules[styleclass][colstrings[i]] ;
						cp->opacityPicker->colors[i] = rules[styleclass][colstrings[i]] ;
						cp->preview->colors[i] = rules[styleclass][colstrings[i]] ;
					
					}
					cp->color=(unsigned char*)data[std::string((const char*) xmlGetProp( node,(const xmlChar*)"value"))];
					return (Panel* )cp;
				}else if (std::string( (const char*)xmlGetProp( node,(const xmlChar*)"type")  )=="float32"){
					ColorPicker<float>* cp=new ColorPicker<float>(
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"x")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"y")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"width")),
						atoi((const char*)xmlGetProp( node,(const xmlChar*)"height")),
						0
					) ;
					
					
					for (char i=0;i<12;i++){
						cp->colorBall->colors[i] = rules[styleclass][colstrings[i]] ;
						cp->brightnessPicker->colors[i] = rules[styleclass][colstrings[i]] ;
						cp->opacityPicker->colors[i] = rules[styleclass][colstrings[i]] ;
						cp->preview->colors[i] = rules[styleclass][colstrings[i]] ;
					
					}
					cp->color=(float*)data[std::string((const char*) xmlGetProp( node,(const xmlChar*)"value"))];
					return (Panel* )cp;
				}
				
				
				
			return (Panel*) 0;
			}}
			
			
			
			};

		static unsigned int loadTexture(const char* filename){
			SDL_Surface* img=SDL_LoadBMP(filename);
			unsigned int id;
			glGenTextures(1,&id);
			glBindTexture(GL_TEXTURE_2D,id);
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img->w,img->h,0,GL_RGBA,GL_UNSIGNED_BYTE,img->pixels);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			SDL_FreeSurface(img);
			return id;
		}
		static Panel* print_xml(xmlNode * node){
	
	std::string name=std::string((const char*)(node->name));

	
	std::string styleclass= std::string((const char*)xmlGetProp( node,(const xmlChar*)"class"));

	Panel *p=factory[name](node,styleclass);
	if (!p){
		std::cout << "xmlNode: "<<name << "not defined\n";
		return 0;
	}
	if (xmlHasProp( node,(const xmlChar*)"bgimage")){
		p->bgimage=loadTexture((const char*)xmlGetProp( node,(const xmlChar*)"bgimage") );
	}
	if (xmlHasProp( node,(const xmlChar*)"onclick")){
		std::string key=(const char*)xmlGetProp( node,(const xmlChar*)"onclick");
		if (data.find(key) == data.end())
			data[key]=0;
		p->mouselistener=((mouseeventlistener) data[key]);
	}
	if (xmlHasProp( node,(const xmlChar*)"onenter")){
		std::string key=(const char*)xmlGetProp( node,(const xmlChar*)"onenter");
		if (data.find(key) == data.end())
			data[key]=0;
		p->mouseenterlistener=((mouseeventlistener) (data[key]));
	}
	if (xmlHasProp( node,(const xmlChar*)"onexit")){
		std::string key=(const char*)xmlGetProp( node,(const xmlChar*)"onexit");
		if (data.find(key) == data.end())
			data[key]=0;
		p->mousexitlistener=((mouseeventlistener) (data[key]));
	}
	if (xmlHasProp( node,(const xmlChar*)"onmousemove")){
		std::string key=(const char*)xmlGetProp( node,(const xmlChar*)"onmousemove");
		if (data.find(key) == data.end())
			data[key]=0;
		p->mousemotionlistener=((mousemotioneventlistener) (data[key]));
	}
	if (xmlHasProp( node,(const xmlChar*)"onmousedrag")){
		std::string key=(const char*)xmlGetProp( node,(const xmlChar*)"onmousedrag");
		if (data.find(key) == data.end())
			data[key]=0;
		p->mousedraglistener=((mousemotioneventlistener) (data[key]));
	}
	
	if (xmlHasProp( node,(const xmlChar*)"onmousemove")){
		std::string key=(const char*)xmlGetProp( node,(const xmlChar*)"onmousemove");
		if (data.find(key) == data.end())
			data[key]=0;
		p->mousemotionlistener=((mousemotioneventlistener) (data[key]));
	}
	if (xmlHasProp( node,(const xmlChar*)"onkeypress")){
		std::string key=(const char*)xmlGetProp( node,(const xmlChar*)"onkeypress");
		if (data.find(key) == data.end())
			data[key]=0;
		p->keydownlistener=((eventlistener) (data[key]));
	}
	if (xmlHasProp( node,(const xmlChar*)"update")){
		std::string key=(const char*)xmlGetProp( node,(const xmlChar*)"update");
		if (data.find(key) == data.end())
			data[key]=0;
		updatefunc udf =((updatefunc)   (data[key]));
		p->update=udf;
		
	}
	if (xmlHasProp( node,(const xmlChar*)"render")){
		std::string key=(const char*)xmlGetProp( node,(const xmlChar*)"render");
		if (data.find(key) == data.end())
			data[key]=0;
		void(*render)(Panel*) =(  ( void(*) (Panel*) )   (data[key])  );
		p->render=render;
		
	}
	if (xmlHasProp( node,(const xmlChar*)"object")){
		std::string key=(const char*)xmlGetProp( node,(const xmlChar*)"object");
		if (data.find(key) == data.end())
			data[key]=0;
		p->object=(RenderObj*) data[key];
		
	}
	
	
	

	for (char i=0;i<12;i++){
		p->colors[i] = rules[styleclass][colstrings[i]] ;
	}
				

		
	
	//makePanel(node);
	
	
	
	for(xmlNodePtr child=node->children;child;child=child->next)
    {

		if(child->type != XML_TEXT_NODE){
			std::string childname=std::string((const char*)(child->name));
			if (childname == "list"){
				int size = atoi((const char*)xmlGetProp( child,(const xmlChar*)"size"));
				std::string datakey=(const char*)xmlGetProp( child,(const xmlChar*)"data");
				void* listdata = data[datakey];
				std::string key=(const char*)xmlGetProp( child,(const xmlChar*)"function");
				for (int i=0;i<size;i++){
					((listfunction) (data[key]) ) (p,listdata,i);
				}
				
			}else{
				Panel* cp=print_xml(child);
				if(cp) {
					p->add(cp);
				}
			}
		}

    }
    
	
	return p;
	
    

}
		void readCss(const char* filename){
			unsigned int col;
			std::stringstream ss;
			char colstring[9];
			char c;
			
			std::ifstream file (filename, std::ios_base::in);
			if (file.is_open())	{
				int colindex=0;
				file.read(&c,1);
				while (c == '#') {
				
					std::stringstream ss;
				
					file.read(colstring,8);
					file.ignore();
					file.read(&c,1);
				
					ss << std::hex << colstring;
				
					ss >> col;
				
					colors[colindex++]= col;
					
				
				}
				std::string line;
				std::string rulename;
				while (!file.eof()){
					if (c=='.'){
						std::getline(file,rulename);
						rules[rulename]={};
					}else if (c=='	'){
						std::string key;
						std::string val;
						getline(file, key, ' ');
						getline(file, val);
						 
						if (key=="font"){
							if (!( fonts[val] ) ){
								fonts[val] = TTF_OpenFont("../res/fonts/Aaargh.ttf", 24);
							} 
							
							rules[rulename][key]=(unsigned int*) fonts[val];
							
							
						}else{
							rules[rulename][key]=&colors[atoi(val.c_str())];
						}
					}
				
				file.read(&c,1);
				}
			}else {
				std::cout << "File Error\n";
			}
			file.close();
		   std::cout << "Closed style file\n";
		}

		int init(std::map<std::string,void*> data0,const char* style_file,const char* xml_file){
			data=data0;
			SDL_Init(SDL_INIT_EVERYTHING);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			TTF_Init();
			//init_ui();
			LIBXML_TEST_VERSION
			
			
			readCss(style_file);

			xmlParserCtxtPtr ctxt; /* the parser context */
			xmlDocPtr doc; /* the resulting document tree */

			ctxt = xmlNewParserCtxt();
			if (!ctxt) {
				fprintf(stderr, "Failed to allocate parser context\n");
				return 0;
			}
			
			doc = xmlCtxtReadFile(ctxt, xml_file, NULL, 0);
			if (!doc) {
				fprintf(stderr, "Failed to parse xml\n");
			}
			
			xmlNodePtr root =xmlDocGetRootElement(doc);

			for(xmlNodePtr child=root->children;child;child=child->next)
			{
				if(child->type != XML_TEXT_NODE){
					windows.push_back((Window*) print_xml(child));
				}
			}
			
			/* free up the parser context */
			xmlFreeParserCtxt(ctxt);


			xmlCleanupParser();
			xmlMemoryDump();
			
			if(glewInit() != GLEW_OK){
				std::cout<<"glewinit failed\n";
				exit(1);
			}
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			return 0;
		}

		int run(){
		
			while (windows.size()){
				for (auto win= windows.begin();win!=windows.end();){
					if (!(*win)->run()){
						auto prev = win++; 
						Window* w=*prev;
						windows.erase(prev);
						delete w;
					}else{
						win++;
					}
				}
			}	
			return 0;
		}
}

#endif
