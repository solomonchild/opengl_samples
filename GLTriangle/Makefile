.PHONY:example clean all
NAME:=example.exe
VARIANT:=debug
CFLAGS:= -g3
INCLUDES:=
LDFLAGS:=
LOCAL_LIBS:= -lglew32 -lglfw3 -lopengl32 -lgdi32


all:$(VARIANT)/$(NAME)

ALLSOURCE:=$(wildcard src/*)
OBJ_FILES := $(addprefix obj/,$(notdir $(ALLSOURCE:.cpp=.o)))

obj/%.o: src/%.cpp
	mkdir -p obj/
	g++ $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(VARIANT)/$(NAME): $(OBJ_FILES)
	mkdir -p $(VARIANT)
	g++ $(OBJ_FILES) $(LDFLAGS) $(LOCAL_LIBS) -o $@ 

clean:
	rm -rf obj debug
