// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_consolas_bold_7_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_consolas_bold_7_usascii'.
//
/* // Example usage:

static stb_fontchar fontdata[STB_SOMEFONT_NUM_CHARS];

static void init(void)
{
    // optionally replace both STB_SOMEFONT_BITMAP_HEIGHT with STB_SOMEFONT_BITMAP_HEIGHT_POW2
    static unsigned char fontpixels[STB_SOMEFONT_BITMAP_HEIGHT][STB_SOMEFONT_BITMAP_WIDTH];
    STB_SOMEFONT_CREATE(fontdata, fontpixels, STB_SOMEFONT_BITMAP_HEIGHT);
    ... create texture ...
    // for best results rendering 1:1 pixels texels, use nearest-neighbor sampling
    // if allowed to scale up, use bilerp
}

// This function positions characters on integer coordinates, and assumes 1:1 texels to pixels
// Appropriate if nearest-neighbor sampling is used
static void draw_string_integer(int x, int y, char *str) // draw with top-left point x,y
{
    ... use texture ...
    ... turn on alpha blending and gamma-correct alpha blending ...
    glBegin(GL_QUADS);
    while (*str) {
        int char_codepoint = *str++;
        stb_fontchar *cd = &fontdata[char_codepoint - STB_SOMEFONT_FIRST_CHAR];
        glTexCoord2f(cd->s0, cd->t0); glVertex2i(x + cd->x0, y + cd->y0);
        glTexCoord2f(cd->s1, cd->t0); glVertex2i(x + cd->x1, y + cd->y0);
        glTexCoord2f(cd->s1, cd->t1); glVertex2i(x + cd->x1, y + cd->y1);
        glTexCoord2f(cd->s0, cd->t1); glVertex2i(x + cd->x0, y + cd->y1);
        // if bilerping, in D3D9 you'll need a half-pixel offset here for 1:1 to behave correct
        x += cd->advance_int;
    }
    glEnd();
}

// This function positions characters on float coordinates, and doesn't require 1:1 texels to pixels
// Appropriate if bilinear filtering is used
static void draw_string_float(float x, float y, char *str) // draw with top-left point x,y
{
    ... use texture ...
    ... turn on alpha blending and gamma-correct alpha blending ...
    glBegin(GL_QUADS);
    while (*str) {
        int char_codepoint = *str++;
        stb_fontchar *cd = &fontdata[char_codepoint - STB_SOMEFONT_FIRST_CHAR];
        glTexCoord2f(cd->s0f, cd->t0f); glVertex2f(x + cd->x0f, y + cd->y0f);
        glTexCoord2f(cd->s1f, cd->t0f); glVertex2f(x + cd->x1f, y + cd->y0f);
        glTexCoord2f(cd->s1f, cd->t1f); glVertex2f(x + cd->x1f, y + cd->y1f);
        glTexCoord2f(cd->s0f, cd->t1f); glVertex2f(x + cd->x0f, y + cd->y1f);
        // if bilerping, in D3D9 you'll need a half-pixel offset here for 1:1 to behave correct
        x += cd->advance;
    }
    glEnd();
}
*/

#ifndef STB_FONTCHAR__TYPEDEF
#define STB_FONTCHAR__TYPEDEF
typedef struct
{
    // coordinates if using integer positioning
    float s0,t0,s1,t1;
    signed short x0,y0,x1,y1;
    int   advance_int;
    // coordinates if using floating positioning
    float s0f,t0f,s1f,t1f;
    float x0f,y0f,x1f,y1f;
    float advance;
} stb_fontchar;
#endif

#define STB_FONT_consolas_bold_7_usascii_BITMAP_WIDTH         128
#define STB_FONT_consolas_bold_7_usascii_BITMAP_HEIGHT         28
#define STB_FONT_consolas_bold_7_usascii_BITMAP_HEIGHT_POW2    32

#define STB_FONT_consolas_bold_7_usascii_FIRST_CHAR            32
#define STB_FONT_consolas_bold_7_usascii_NUM_CHARS             95

#define STB_FONT_consolas_bold_7_usascii_LINE_SPACING           5

static unsigned int stb__consolas_bold_7_usascii_pixels[]={
    0x06442600,0x89b1a166,0x4370e640,0x828a254e,0xb87330ba,0x31a8dd41,
    0x17709862,0x70351ec5,0x442ee237,0x1161a82b,0xb8550dcb,0xa920ee60,
    0x5e5266e5,0x9555cb2c,0x57770bea,0x65e4ef2e,0x4ae33972,0x646a398c,
    0x8b0ec0cd,0x45951cab,0x8b6a0d98,0x21b8723a,0x441b10c8,0x17994869,
    0x49b53772,0x3d12ec4b,0x99b95c6c,0x646d26d3,0x8e632372,0x8b70aa08,
    0xea936a0c,0x57773644,0x44371a58,0x21a0b10c,0x66649f54,0xb16931b4,
    0x976d4689,0x93190ddb,0xc84cea36,0xdc8ee398,0xdb9220a3,0x4ae1640c,
    0x8d342b8d,0x0170a61b,0xc9e5c90d,0x21bd32cc,0x39903665,0xd98572a8,
    0x2e7bd30d,0x3221bb52,0x06c79171,0x33bac86c,0x4372a1bb,0xd9262dda,
    0x20e446e0,0x951a663a,0x0ce437ae,0x0a8f4b2a,0x00442200,0x00010000,
    0x002a88cc,0x25983600,0x9860311b,0x5070d40a,0x006a1303,0x00000000,
    0x00000000,0x04410100,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x54770000,0x11dc2a81,0x2e235079,
    0x17305cc3,0x1bb98ee2,0x2a8a28ee,0x982ea06a,0x0d45732d,0x09898ae6,
    0x26263133,0x19898311,0x23bb86ee,0x57572cab,0x9896166e,0x9ca87265,
    0x26259110,0x92c1951e,0x4cdcb2ee,0x06c13950,0x8eee3b77,0x55372cbb,
    0x6e64e372,0x45ab8733,0x4ef2e3e9,0x4dd14dad,0x20ea09fa,0x0e437725,
    0x44a8b72a,0x2957b0eb,0x4b771bcc,0xb96f5c2b,0x259970dc,0x57372bab,
    0x6664eb32,0x02eb8733,0x6ce66e59,0x2595739b,0x2c162e9d,0x70b27537,
    0x931625bb,0x4d33361b,0x447b71cd,0xab8360de,0x6dcaa6e6,0x4e4b7aa2,
    0x2693593e,0x36e265c3,0x261bb70e,0x23bb50dd,0xa8913ecc,0x4477665d,
    0x37ae02de,0x0797b022,0x3600ecdc,0x4dcae6e0,0x2900372a,0xde9a493d,
    0x00859371,0x00540000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x15c1a800,0x2a1c45b3,0x8ae1c1bb,0x19857109,0x1bb98ae2,0x26388266,
    0x082ae639,0x85dcca25,0x4662a311,0x17710bb8,0x4ca286ea,0x3712ec2b,
    0x932542a8,0xab876217,0x32b2352c,0x6ccc7b51,0x3663b531,0xccb9b22d,
    0x5dc977b2,0x47911bab,0x1b95398c,0x4e54272a,0x2765b5b0,0x26395739,
    0xa85710db,0x45706c42,0x0e6360d9,0x8398f332,0xdc99a20d,0x54dcb730,
    0x322935b2,0x321b8bb1,0xda93a3dd,0x3619d50b,0x23975498,0x5db70edb,
    0xd88aa154,0xa96215c0,0x64c590de,0xb8590e62,0x6ecbbb22,0x3655373f,
    0x42b8249a,0x44ea321b,0xba872a6d,0x6c4ea360,0x46cee6e6,0x2a3db549,
    0x015c01ed,0xea936a00,0x345df72e,0x00b112a6,0x6f543700,0x27273191,
    0xdea8753b,0x2741bbb1,0x00001bb7,0x00000000,0x00000000,0x00000000,
    0x0bb98000,0x22512945,0x231130ba,0x4104c1a8,0xa8261cca,0x31a54911,
    0x312e2333,0x00000003,0x22000000,0x2933b0ea,0x55b52aab,0x77443762,
    0x4f217710,0xa9321bb9,0x2a5b3701,0x449712aa,0x0000003b,0x20000000,
    0x44f7361d,0x9760aa5d,0x39b50bb9,0x4c541110,0x00000001,0x00000000,
    0x6fd40000,0x26c5b991,0x02cbb855,0x000000d4,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,
};

static signed short stb__consolas_bold_7_usascii_x[95]={ 0,1,0,0,0,0,0,1,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0, };
static signed short stb__consolas_bold_7_usascii_y[95]={ 5,0,0,0,-1,0,0,0,-1,-1,0,1,3,2,
3,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,1,0,1,0,1,0,1,0,0,
0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,-1,0,2, };
static unsigned short stb__consolas_bold_7_usascii_w[95]={ 0,2,4,4,4,4,4,2,4,3,4,4,3,3,
2,4,4,4,4,4,4,4,4,4,4,4,2,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,2,4,3,4,4,3,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,2,4,4, };
static unsigned short stb__consolas_bold_7_usascii_h[95]={ 0,6,2,5,7,6,6,2,8,8,4,4,4,2,
3,6,6,5,5,6,5,6,6,5,6,5,5,6,5,3,5,6,7,5,5,6,5,5,5,6,5,5,6,5,
5,5,5,6,5,7,5,6,5,6,5,5,5,5,5,7,6,7,3,2,2,5,6,5,6,5,5,6,5,5,
7,5,5,4,4,5,6,6,4,5,6,5,4,4,4,6,4,7,8,7,2, };
static unsigned short stb__consolas_bold_7_usascii_s[95]={ 127,80,111,104,32,92,21,94,5,1,71,
76,124,116,81,26,11,89,94,117,109,112,36,99,16,84,81,88,71,84,61,
97,37,46,41,41,31,26,21,75,11,6,31,121,116,111,106,70,96,42,86,
1,66,83,36,61,16,1,51,47,102,28,89,106,97,46,6,76,122,66,81,
107,91,51,23,71,56,119,114,76,65,60,61,56,55,101,56,51,66,50,46,
18,10,13,101, };
static unsigned short stb__consolas_bold_7_usascii_t[95]={ 1,1,22,16,1,1,10,22,1,1,22,
22,16,22,22,10,10,16,16,1,16,1,10,16,10,16,16,1,16,22,16,
1,1,16,17,10,17,17,17,1,17,17,10,10,10,10,10,1,10,1,10,
10,16,1,17,10,17,17,10,1,1,1,22,22,22,10,10,10,1,10,10,
1,10,16,1,10,16,16,16,16,1,1,22,10,1,10,22,22,22,1,22,
1,1,1,22, };
static unsigned short stb__consolas_bold_7_usascii_a[95]={ 62,62,62,62,62,62,62,62,
62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,
62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,
62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,
62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,
62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,
62,62,62,62,62,62,62, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_consolas_bold_7_usascii_BITMAP_HEIGHT or STB_FONT_consolas_bold_7_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_consolas_bold_7_usascii(stb_fontchar font[STB_FONT_consolas_bold_7_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_consolas_bold_7_usascii_BITMAP_HEIGHT][STB_FONT_consolas_bold_7_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__consolas_bold_7_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_consolas_bold_7_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_consolas_bold_7_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_consolas_bold_7_usascii_BITMAP_WIDTH-1; ++i) {
                unsigned int value;
                if (numbits==0) bitpack = *bits++, numbits=32;
                value = bitpack & 1;
                bitpack >>= 1, --numbits;
                if (value) {
                    if (numbits < 3) bitpack = *bits++, numbits = 32;
                    data[j][i] = (bitpack & 7) * 0x20 + 0x1f;
                    bitpack >>= 3, numbits -= 3;
                } else {
                    data[j][i] = 0;
                }
            }
        }
    }

    // build font description
    if (font != 0) {
        float recip_width = 1.0f / STB_FONT_consolas_bold_7_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_consolas_bold_7_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__consolas_bold_7_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__consolas_bold_7_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__consolas_bold_7_usascii_s[i] + stb__consolas_bold_7_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__consolas_bold_7_usascii_t[i] + stb__consolas_bold_7_usascii_h[i]) * recip_height;
            font[i].x0 = stb__consolas_bold_7_usascii_x[i];
            font[i].y0 = stb__consolas_bold_7_usascii_y[i];
            font[i].x1 = stb__consolas_bold_7_usascii_x[i] + stb__consolas_bold_7_usascii_w[i];
            font[i].y1 = stb__consolas_bold_7_usascii_y[i] + stb__consolas_bold_7_usascii_h[i];
            font[i].advance_int = (stb__consolas_bold_7_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__consolas_bold_7_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__consolas_bold_7_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__consolas_bold_7_usascii_s[i] + stb__consolas_bold_7_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__consolas_bold_7_usascii_t[i] + stb__consolas_bold_7_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__consolas_bold_7_usascii_x[i] - 0.5f;
            font[i].y0f = stb__consolas_bold_7_usascii_y[i] - 0.5f;
            font[i].x1f = stb__consolas_bold_7_usascii_x[i] + stb__consolas_bold_7_usascii_w[i] + 0.5f;
            font[i].y1f = stb__consolas_bold_7_usascii_y[i] + stb__consolas_bold_7_usascii_h[i] + 0.5f;
            font[i].advance = stb__consolas_bold_7_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_consolas_bold_7_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_consolas_bold_7_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_consolas_bold_7_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_consolas_bold_7_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_consolas_bold_7_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_consolas_bold_7_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_consolas_bold_7_usascii_LINE_SPACING
#endif
