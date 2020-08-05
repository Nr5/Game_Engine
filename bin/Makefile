export MESA_GL_VERSION_OVERRIDE=3.0 command
CC = g++
CFLAGS = -lGLEW -lg -lGL -lGLU -lm -lxml2 -lSDL2 -lSDL2_ttf -lSDL2_image -std=c++17
ShaderProgram.o: ../src/ShaderProgram.cpp ../src/ShaderProgram.h
	$(CC) $(CFLAGS) ../src/ShaderProgram.cpp ../src/ShaderProgram.h -c
RenderObj.o: ../src/RenderObj.cpp ../src/RenderObj.h
	$(CC) $(CFLAGS) ../src/RenderObj.cpp ../src/RenderObj.h -c
Skybox.o: ../src/Skybox.cpp ../src/Skybox.h
	$(CC) $(CFLAGS) ../src/Skybox.cpp ../src/Skybox.h -c
Window.o: ../src/Window.cpp ../src/Window.h
	$(CC) $(CFLAGS) ../src/Window.cpp ../src/Window.h  -c

VListLayout.o: ../src/ui/VListLayout.cpp ../src/ui/VListLayout.h
	$(CC) $(CFLAGS)  ../src/ui/VListLayout.cpp ../src/ui/VListLayout.h -c
	
	
Panel.o: ../src/ui/Panel.cpp ../src/ui/Panel.h
	$(CC) $(CFLAGS) ../src/ui/Panel.h -c ../src/ui/Panel.cpp
Label.o: ../src/ui/Label.h ../src/ui/Label.cpp ../src/ui/Panel.h
	$(CC) $(CFLAGS) ../src/ui/Label.cpp ../src/ui/Label.h -c
ColorPicker.o: ../src/ui/ColorPicker.cpp ../src/ui/ColorPicker.h
	$(CC) $(CFLAGS)  ../src/ui/ColorPicker.cpp ../src/ui/ColorPicker.h -c
Checkbox.o: ../src/ui/Checkbox.cpp ../src/ui/Checkbox.h
	$(CC) $(CFLAGS) ../src/ui/Checkbox.cpp ../src/ui/Checkbox.h -c
Slider.o: ../src/ui/Slider.cpp ../src/ui/Slider.h
	$(CC) $(CFLAGS) ../src/ui/Slider.cpp ../src/ui/Slider.h -c
ScrollPane.o: ../src/ui/ScrollPane.cpp ../src/ui/ScrollPane.h
	$(CC) $(CFLAGS) ../src/ui/ScrollPane.cpp ../src/ui/ScrollPane.h -c

UI.o: ../src/ui/UI.h
	$(CC) $(CFLAGS) -I/usr/include/libxml2 ../src/ui/UI.h -c

all: UI.o Panel.o  ScrollPane.o Slider.o Checkbox.o Label.o  VListLayout.o Window.o Skybox.o RenderObj.o ShaderProgram.o ColorPicker.o
clean: 
	rm *.o
