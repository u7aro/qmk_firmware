MOUSEKEY_ENABLE = no
RGB_MATRIX_ENABLE = WS2812

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/glcdfont.c \
        ./lib/logo_reader.c \
        layer_state_reader.c \
        typecount_render.c \
        wpm.c \
