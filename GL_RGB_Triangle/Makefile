.PHONY:example clean all
NAME:=example.exe
VARIANT:=debug
CFLAGS:= -g3
INCLUDES:= -Iinclude
LDFLAGS:=
LOCAL_LIBS:= -lglew32 -lglfw3 -lopengl32 -lgdi32 -lglu32


all:$(VARIANT)/$(NAME)

ALLSOURCE:=$(wildcard src/*)
OBJ_FILES := $(addprefix obj/,$(notdir $(ALLSOURCE:.cpp=.o)))
DEPS := $(OBJ_FILES:.o=.d)


obj/%.o: src/%.cpp
	mkdir -p obj/
	g++ $(CFLAGS) $(INCLUDES) -c -MMD -MP $< -o $@ 

$(VARIANT)/$(NAME): $(OBJ_FILES)
	mkdir -p $(VARIANT)
	g++ $(OBJ_FILES) $(LDFLAGS) $(LOCAL_LIBS) -o $@ 

clean:
	rm -rf obj debug

-include $(DEPS)

