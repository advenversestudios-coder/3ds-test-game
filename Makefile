TARGET  := 3ds-test-game
BUILD   := build
SOURCES := source
INCLUDES := include
LIBS    := -lcitro2d -lcitro3d -lctru -lm
ARCH    := -march=armv6k -mtune=mpcore -mfloat-abi=hard
CFLAGS  := -g -Wall -O2 -mword-relocations $(ARCH)
CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions

ifeq ($(strip $(DEVKITARM)),)
$(error Please set DEVKITARM in your environment)
endif

include $(DEVKITARM)/3ds_rules

CFILES   := $(wildcard $(SOURCES)/*.c)
CXXFILES := $(wildcard $(SOURCES)/*.cpp)
SFILES   := $(wildcard $(SOURCES)/*.s)
OFILES   := $(CFILES:.c=.o) $(CXXFILES:.cpp=.o) $(SFILES:.s=.o)

.PHONY: all clean

all: $(TARGET).3dsx

$(TARGET).elf: $(OFILES)
	$(CXX) $(ARCH) -Wl,-Map,$(TARGET).elf.map -specs=3dsx.specs \
	-o $@ $(OFILES) $(LIBS)

$(TARGET).3dsx: $(TARGET).elf
	3dsxtool $(TARGET).elf $(TARGET).3dsx

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -I$(DEVKITPRO)/libctru/include \
	-I$(DEVKITPRO)/citro2d/include -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) -I$(DEVKITPRO)/libctru/include \
	-I$(DEVKITPRO)/citro2d/include -c $< -o $@

%.o: %.s
	$(CC) -MMD -MP $(ARCH) -I$(DEVKITPRO)/libctru/include -c $< -o $@

clean:
	rm -rf build $(TARGET).elf $(TARGET).elf.map $(TARGET).3dsx
