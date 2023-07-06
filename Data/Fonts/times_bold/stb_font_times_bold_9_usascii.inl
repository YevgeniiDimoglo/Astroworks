// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_times_bold_9_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_times_bold_9_usascii'.
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

#define STB_FONT_times_bold_9_usascii_BITMAP_WIDTH         128
#define STB_FONT_times_bold_9_usascii_BITMAP_HEIGHT         36
#define STB_FONT_times_bold_9_usascii_BITMAP_HEIGHT_POW2    64

#define STB_FONT_times_bold_9_usascii_FIRST_CHAR            32
#define STB_FONT_times_bold_9_usascii_NUM_CHARS             95

#define STB_FONT_times_bold_9_usascii_LINE_SPACING           6

static unsigned int stb__times_bold_9_usascii_pixels[]={
    0x88260984,0x04cc4141,0x22150198,0x40660012,0x198aaa22,0x3306218c,
    0x2066060c,0x135100a8,0x43813530,0x240c82a6,0x4f419866,0x2d1621d8,
    0x6c7a1c28,0x4ddb9e61,0x539c7575,0x43726755,0x0b2ee1c3,0x263b0759,
    0x262996c4,0x0e415343,0xabb944b3,0x225b9aa2,0x8f5cb345,0x50b16e6a,
    0x6dc6fea3,0x64c3d74c,0x5e415075,0x862be25b,0x08d50469,0x82a190ee,
    0x2b253c44,0x7b9b219d,0xa8ecd162,0x146a96e5,0x223fb124,0x887ee0ab,
    0x31429998,0x576e299b,0x32199723,0x2170ee05,0x2788710a,0x7986f1f2,
    0xb3458932,0x2e7996a3,0x95924044,0xc84b6ee9,0x1c57d385,0x5e8cb8ec,
    0x3d49b354,0x82a68730,0xe989e21c,0x2ee089ea,0x4d1620ca,0x9aa83665,
    0x4331a20b,0xb8e71bb9,0x37b1c2ba,0x7cc35114,0x2ee0debc,0x5565c3d9,
    0x20a9a1c0,0x3051e60d,0x45883f10,0x80000716,0x08810800,0x00000408,
    0x98400010,0x71188261,0x40333105,0x251141a8,0x00000000,0x00000000,
    0x00000000,0x00000000,0x982a3530,0x8cc2a61a,0x288aa8a9,0x98a20d4c,
    0x46a6330a,0x7710530a,0x88aaaa67,0x4c1514c1,0x30a60442,0x42980cc3,
    0xf88441aa,0x26395450,0x23e6130f,0x83f050f9,0x8a5f109e,0x42d453e8,
    0x27e53bbc,0x5f885309,0x071e5545,0xa95dccd3,0xb11fa985,0x43e0dc59,
    0x4f60baa1,0x4dfc5741,0x03ea1f80,0x3fa831d7,0x7911c6cc,0x41d41f81,
    0x21d81bfa,0xbb9af223,0xb057d54b,0x85d31654,0x44fb830f,0x4f5c09fa,
    0x443f01eb,0x1b609f06,0x0aca87b3,0x2216a0fc,0x510c43f9,0x77934ddc,
    0xf51e36ab,0x5e4bb265,0x250c7e3c,0x442740e8,0x45c1f8af,0x1ec1a21f,
    0xdd31f44c,0x3e2e6545,0x7b842d41,0xd1790a04,0xf5aa55dc,0x79488570,
    0x70ce64b5,0x20370737,0x31ab2124,0x545d881f,0x27aa3f74,0x4433530f,
    0x8ea35c3f,0xd9871644,0x5433226b,0xb8af23ad,0x037b109c,0x00000000,
    0x00000000,0x00800000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x20d54c00,0x40aa9829,0x8af2a3ab,
    0x4c2a60a9,0x531a881a,0x555510cc,0x31544d4c,0x46aaa235,0x2a61aaa9,
    0x2a61881a,0x2972441a,0xf8988aa3,0x7c16a6b8,0x4d3972d9,0x976278da,
    0x7c07e25d,0x132d4171,0x5d1f85f1,0x4a1f0fc4,0x3e2388f8,0x893625b8,
    0xf1144c8f,0x547f2a31,0x74cd31f4,0xc9ec7c3b,0x07d6a68b,0xf8b731f5,
    0xb5073f00,0x3a1f0b90,0x831f07c2,0xf87c429f,0x991f12e1,0x8ec26c08,
    0x4c3f7f28,0x315fc69d,0x2df54d7b,0xf16e7362,0x503b7e01,0xbf80f98b,
    0x7f07c2ea,0x7c43bf89,0x3e25c7f0,0x751e62db,0x9b1f0488,0x03e346cc,
    0x220b5344,0x87c5b8fa,0x2a2ec7c0,0x3e089f45,0x3e0f85d0,0x10c47c08,
    0x25c3f11f,0x4c51e63e,0x26045c08,0x5d52f8af,0xd9817ccf,0x4e530950,
    0xb57f30ec,0x86fc57cc,0x3aabee6b,0x47f15f30,0x985f32f9,0x2fe65abf,
    0xf986e42c,0x706e03bb,0x000007ff,0x00000000,0x00000000,0x00000000,
    0x8023b800,0x19801509,0x4655dc91,0x6544e972,0x5124c140,0x9926ea17,
    0x9da8aa2a,0x86f260c1,0x5e54118a,0x3b350443,0x812aef2a,0x711e882b,
    0x142ba837,0x2213f3d3,0x85b5518f,0xbb8555c3,0x5cd3b34a,0x743b950d,
    0x1d306543,0xa6567661,0x2aa669e9,0x46ccb711,0x21b601f7,0xb8ecc1ea,
    0x6574080c,0x597126c4,0x1e46f6ee,0x4ecd2af2,0x41e57626,0x1663a46b,
    0x1b328e2e,0x3f10bc8d,0x30fbc6cc,0xd187e263,0x2e206ea3,0x98b8d10b,
    0x79971542,0x885f4c38,0x4d7d11bb,0x217d349b,0x86113ea9,0x3aa0806a,
    0x5b90d46a,0x3e3e7aa5,0x92ecd4a1,0x040029fd,0x00c00000,0x00000000,
    0x00000000,0x0bea5700,0x0000003d,0x00000000,0x00000000,0x00000000,
    0x31bbbb80,0x82661159,0x00003bbb,0x00000000,0x00000000,0x33000000,
    0x514c2133,0x00000037,0x00000000,0x00000000,0x98800000,0x00000099,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,
};

static signed short stb__times_bold_9_usascii_x[95]={ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,
-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };
static signed short stb__times_bold_9_usascii_y[95]={ 7,1,1,1,1,1,1,1,1,1,1,2,5,4,
5,1,1,1,1,1,1,1,1,1,1,1,3,3,2,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,1,3,1,3,1,3,1,3,1,1,
1,1,1,3,3,3,3,3,3,3,1,3,3,3,3,3,3,1,1,1,4, };
static unsigned short stb__times_bold_9_usascii_w[95]={ 0,3,4,4,4,8,7,2,3,3,4,5,2,3,
2,3,4,4,4,4,4,4,4,4,4,4,3,3,5,5,5,4,8,6,6,6,6,6,5,7,7,3,5,7,
6,8,6,7,5,7,6,5,6,6,6,9,6,6,6,3,3,2,5,6,2,4,5,4,5,4,4,4,5,3,
4,5,3,7,5,4,5,5,4,3,3,5,4,6,4,4,4,3,2,3,5, };
static unsigned short stb__times_bold_9_usascii_h[95]={ 0,7,4,7,7,7,7,4,8,8,4,5,4,2,
3,7,7,6,6,7,6,7,7,7,7,7,5,6,5,3,5,7,8,6,6,7,6,6,6,7,6,6,7,6,
6,6,7,7,6,8,6,7,6,7,7,7,6,6,6,8,7,8,4,1,2,5,7,5,7,5,6,6,6,6,
8,6,6,4,4,5,6,6,4,5,7,5,5,5,4,6,4,8,8,8,2, };
static unsigned short stb__times_bold_9_usascii_s[95]={ 126,61,93,75,80,85,103,125,1,45,107,
46,98,25,125,13,23,99,120,34,8,39,44,65,70,98,25,111,19,13,13,
8,21,1,104,119,92,85,79,111,67,75,79,48,41,32,1,53,14,30,1,
56,115,49,62,69,97,90,60,38,94,42,82,29,125,41,28,52,17,72,85,
110,8,122,16,104,56,117,101,57,26,20,88,68,49,62,36,29,77,115,112,
12,9,5,19, };
static unsigned short stb__times_bold_9_usascii_t[95]={ 1,1,25,1,1,1,1,18,1,1,25,
25,25,31,23,10,10,18,18,10,25,10,10,1,1,1,25,18,25,31,25,
10,1,25,18,1,18,18,18,1,18,18,9,18,18,18,10,1,18,1,18,
9,9,9,9,9,9,9,18,1,1,1,25,31,27,25,10,25,10,25,9,
9,18,9,1,9,18,25,25,25,18,18,25,25,1,25,25,25,25,18,25,
1,1,1,31, };
static unsigned short stb__times_bold_9_usascii_a[95]={ 33,43,72,65,65,130,108,36,
43,43,65,74,33,43,33,36,65,65,65,65,65,65,65,65,
65,65,43,43,74,74,74,65,121,94,87,94,94,87,79,101,
101,51,65,101,87,123,94,101,79,101,94,72,87,94,94,130,
94,94,87,43,36,43,76,65,43,65,72,58,72,58,43,65,
72,36,43,72,36,108,72,65,72,72,58,51,43,72,65,94,
65,65,58,51,29,51,68, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_times_bold_9_usascii_BITMAP_HEIGHT or STB_FONT_times_bold_9_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_times_bold_9_usascii(stb_fontchar font[STB_FONT_times_bold_9_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_times_bold_9_usascii_BITMAP_HEIGHT][STB_FONT_times_bold_9_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__times_bold_9_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_times_bold_9_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_times_bold_9_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_times_bold_9_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_times_bold_9_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_times_bold_9_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__times_bold_9_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__times_bold_9_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__times_bold_9_usascii_s[i] + stb__times_bold_9_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__times_bold_9_usascii_t[i] + stb__times_bold_9_usascii_h[i]) * recip_height;
            font[i].x0 = stb__times_bold_9_usascii_x[i];
            font[i].y0 = stb__times_bold_9_usascii_y[i];
            font[i].x1 = stb__times_bold_9_usascii_x[i] + stb__times_bold_9_usascii_w[i];
            font[i].y1 = stb__times_bold_9_usascii_y[i] + stb__times_bold_9_usascii_h[i];
            font[i].advance_int = (stb__times_bold_9_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__times_bold_9_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__times_bold_9_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__times_bold_9_usascii_s[i] + stb__times_bold_9_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__times_bold_9_usascii_t[i] + stb__times_bold_9_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__times_bold_9_usascii_x[i] - 0.5f;
            font[i].y0f = stb__times_bold_9_usascii_y[i] - 0.5f;
            font[i].x1f = stb__times_bold_9_usascii_x[i] + stb__times_bold_9_usascii_w[i] + 0.5f;
            font[i].y1f = stb__times_bold_9_usascii_y[i] + stb__times_bold_9_usascii_h[i] + 0.5f;
            font[i].advance = stb__times_bold_9_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_times_bold_9_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_times_bold_9_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_times_bold_9_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_times_bold_9_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_times_bold_9_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_times_bold_9_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_times_bold_9_usascii_LINE_SPACING
#endif

