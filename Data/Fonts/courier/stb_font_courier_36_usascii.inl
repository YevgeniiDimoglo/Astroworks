// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_courier_36_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_courier_36_usascii'.
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

#define STB_FONT_courier_36_usascii_BITMAP_WIDTH         256
#define STB_FONT_courier_36_usascii_BITMAP_HEIGHT        124
#define STB_FONT_courier_36_usascii_BITMAP_HEIGHT_POW2   128

#define STB_FONT_courier_36_usascii_FIRST_CHAR            32
#define STB_FONT_courier_36_usascii_NUM_CHARS             95

#define STB_FONT_courier_36_usascii_LINE_SPACING          17

static unsigned int stb__courier_36_usascii_pixels[]={
    0x06a09880,0x510a8050,0x02aaaaa0,0x0a800000,0x4c055555,0x00000030,
    0x01623a80,0x00157510,0x70002da8,0x93007bdb,0x22019ddd,0xaaaaaaaa,
    0x40174c0a,0x203dedb9,0x980cdedb,0xaaaaaaaa,0x7dc00aaa,0x7c417f62,
    0xf31fea80,0x5fdddb05,0x00007c40,0xeeef97c4,0x7d3f880e,0x7f644000,
    0x4b9000de,0xffd1007a,0x9801dffd,0x002ec9ce,0xdf95bfb1,0x2b37f601,
    0xefa83ffd,0x2eeeeeee,0xfb102fec,0x981b959d,0x1ffdbdfe,0x777777ec,
    0x401feeee,0x417442fb,0xd84e80f8,0x2202f806,0x7b80000f,0x43f2007e,
    0xdd30007b,0x001df737,0x4c035499,0x17e4c1df,0x005883b0,0x86d881fb,
    0x2fb881ec,0x7e4003d4,0x001df505,0xfc881bf1,0x3e201360,0x5c17dc01,
    0x7cc0f885,0x7c03fa80,0x00b3ee02,0x00fc7d00,0x007f13e2,0x01b60bd0,
    0x4c06b936,0x417dc04f,0x9803b058,0xb85f101f,0x1ea37400,0x2617f200,
    0x03f2004f,0x200ae5f8,0x8098807a,0x540f887a,0x5f01ba06,0xfedffb88,
    0x7d4005de,0x3f9007e0,0x7d4006b8,0xd801f300,0x09d016e3,0x41261b20,
    0x202ec02b,0x0fa8005d,0x3ee001ea,0x74005e84,0x4003e404,0x3d40004d,
    0x81aa07c4,0xb0be01fb,0x06fc985d,0x007e2740,0x005f10df,0x00fa01fc,
    0xf502e47d,0x20fe2001,0x05f00d06,0x54000fa8,0x2001ea0f,0x007e44fb,
    0x1f300be0,0x0002f800,0x207c43d4,0x817e206a,0xd807e22f,0xf03ea006,
    0xc817d403,0x801f3006,0x9917404c,0x2e002740,0x9910cb87,0x4400f880,
    0x22ec001f,0x3fb8007a,0x2ec0017c,0xf5001b20,0xaaaaaaa8,0x443d42aa,
    0x3603540f,0x2e45f00f,0x4e800620,0x81f601f8,0x07a801f8,0x5f013a62,
    0x003f026c,0xdea80f88,0x03cc103e,0x3ea002f8,0xdcc9bd42,0x447f501b,
    0x01f50007,0xb9000fe2,0xeeeeeed8,0x443d45ee,0x3203540f,0x2ec5f02f,
    0x01f30000,0x01be203f,0x30b700b9,0xd989fffd,0xefeeefee,0x003e25ee,
    0x980807e0,0x00d50eeb,0xfca980fa,0xffffa82f,0xfa83fecd,0x59931aa2,
    0x710bed80,0x2f8001bd,0x1ea2dc00,0x80d703e2,0x5c5f04fb,0xbb00001f,
    0x2fcc07e0,0x99007e60,0x4c8bdf98,0x667e65c4,0x263ccdfc,0x005d0007,
    0xb817dd73,0x6c07b006,0x7b303fff,0xf989f503,0x6ffcd322,0x3f200efe,
    0x8004ffef,0x2dc000f9,0x81f107e2,0x82fd405d,0x0567ec2f,0xf01f9800,
    0x2013ea03,0x3a26405d,0x1f302646,0x0079817c,0x3b2605d0,0x01ae00bd,
    0x7dcc01ec,0x43f50003,0x3e7362f9,0x203b6a1c,0xeedcdfd8,0x002e4000,
    0x85fec2dc,0x03fb30f8,0x05f06f88,0x05bdffb3,0x03f02e40,0x3e600fee,
    0x2f893200,0xf8f30264,0x0001f101,0x5ef64c3f,0x200d7000,0x17a6003d,
    0x3f126c00,0x9d027edc,0xec80ce88,0x000fa001,0x4bfe616e,0x00bfd0f8,
    0x00be0df1,0x801df953,0x407e02f8,0x09d002fc,0xc81f3264,0x1f89ea04,
    0xf30007e0,0x64c05641,0x3a00f501,0x00fc4002,0x41f12e40,0x23d406fa,
    0x8036405d,0x5b8000f8,0x83e20df8,0x2fcc03fa,0x362002f8,0x3e036406,
    0x2007f701,0xe89900fa,0x2aa62643,0xabfbaafc,0x2002740a,0xade9807b,
    0x007cc1ec,0x26c000fc,0x30235c00,0x20f8803f,0x007c400f,0x5b80035c,
    0x03e207cc,0x04fa80b9,0x1f88005f,0x1f805f10,0x74009f50,0xcfa89904,
    0xfffe89b1,0xffffffff,0x88007d42,0x4c1c803f,0x2200fc45,0x06b8000f,
    0x0f805c80,0x00f31f80,0x00f600ba,0x21ea2dc0,0x203540f8,0x0c5f03fb,
    0x0d703e80,0x1be603f0,0x5c80fa80,0x0ffffda8,0x403ccb70,0x00d9005e,
    0x7d0360d1,0x90007b80,0x009b000b,0x30f9805d,0x100be00f,0x16e0003f,
    0xa81f10f5,0xf80fe406,0x5f300d52,0x07e00fe0,0x1fc007f8,0x3531035c,
    0x00f52e40,0x1fc809f3,0x85704a80,0x0027407b,0x30009f44,0x80d7003f,
    0x3007e26b,0x006a801f,0x10f516e0,0x7406a81f,0x27dcbe06,0x03dc1ba0,
    0x03f201f8,0x0f986b80,0xd726c000,0x307be600,0x834003fb,0xb81fc40e,
    0x3600f60f,0xe8803b66,0x1ec1edc5,0x07642f88,0x09b009d0,0x1ea2dc00,
    0x40d503e2,0x5cbe03f9,0xca89beff,0x007d01ff,0x04f9807e,0x0fa0be20,
    0x2dc7b000,0xfdff9100,0x3c8001df,0x0bfb825c,0xefa87f71,0x107f540a,
    0xeea837fb,0x107ffe60,0x82f545bf,0x077542ee,0x70000fc0,0x0f887a8b,
    0x01fb0354,0xfc8c997c,0x500cffff,0x007e001f,0x86c800fd,0x1f40006b,
    0xbf7000b9,0x2e200015,0x2a00cece,0x102ffeff,0x9ffdffd9,0x3bff6a01,
    0xfff884ff,0xffffd980,0x7f7fdc04,0x00d3004f,0x43545b80,0x883d40f8,
    0x3017c05f,0x009d003f,0x0bea00fc,0xee82f880,0x17401700,0xcfc80099,
    0x005c41aa,0x1a980030,0x026aa200,0x2009a980,0x554401a8,0x13531000,
    0xb8000000,0x07c426c5,0x07f207e2,0x07c405f0,0xf8003e60,0x4006e801,
    0xacee986c,0x3e00eeba,0x74401362,0xdfffffff,0x00001efd,0x00000000,
    0x00000000,0x00000000,0x81fc9a6c,0x0aec80f8,0x2666217e,0x003e202f,
    0x9bf800bb,0x003f5019,0x76440fc4,0x7400abdf,0x64400b20,0x1665441b,
    0x00000000,0x00000000,0x00000000,0x97c40000,0x203a01de,0x01d32fb8,
    0x405ffffd,0x07e600f8,0x3fffff00,0xbb000f60,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x000007e4,0x06800000,0x00000144,
    0x001c4000,0x00000000,0x00000000,0x00000000,0x00000000,0x2aa60000,
    0x001ffcaa,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0xffff8800,0x00000cef,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x2a003100,0x000001aa,0xa8055550,0x2a602ded,0x800000aa,
    0x3019aaa8,0x00155555,0x0bdedb88,0xaaa86aaa,0x2b3b6e61,0x37b2e000,
    0x02aaa22b,0x5554c000,0x5555500a,0x0002aaa8,0x00055cc0,0xfd8002a2,
    0x27f6c400,0xed800000,0x2f3f206e,0xeea81ffd,0x2200001f,0xffffeffd,
    0x7f7775c0,0x33bea000,0xef8afecb,0x29fdd14e,0xfecbcdfc,0x5eff4c02,
    0xefa8efdb,0x4005a82e,0xb02eefeb,0x76c1dfdd,0xf700006e,0x007bfddf,
    0x2005fff5,0x132000fd,0xd5000000,0xd9107ee0,0x00001f80,0x03302bba,
    0x2a001f10,0x3f7f503f,0x80f6ee40,0x19f302fb,0x80d9db10,0x1f88006b,
    0x35409b00,0x2bf62000,0xb013ea20,0x3600dfff,0x0132000f,0x0d500000,
    0x026c05f1,0x2a00003f,0x7c40001f,0x403f8800,0x3f201ffa,0x441fa806,
    0x06fd804e,0x5c80035c,0x2a00f980,0x07740006,0x7dc07f30,0x031004ff,
    0x00004c80,0x35435400,0x0fc07e20,0x005c8000,0xc800f880,0x403f9006,
    0x89b001fc,0x0df1006b,0xf10006b8,0x5405d803,0x03ee0006,0xdb807e20,
    0x2000000b,0x0000004c,0x402e4354,0x0003f02e,0x20001320,0x03e800f8,
    0x36403f50,0x04d8d500,0x2aa61b60,0xaaaaaaed,0x9817201a,0x0035401f,
    0x32003f88,0x00000006,0x3b6e24c8,0x2e6000bd,0x21aa1bdd,0xf04b804c,
    0x0b3b6e63,0x55db5550,0x20015555,0x02f800f8,0x2e403f10,0x17c1f100,
    0xdd70d700,0xddddddfd,0x80fc409d,0xa86a805d,0x35c1aaaa,0x0003e200,
    0x0aaaaa98,0x77dd3200,0x402fecbc,0xfdbbdfe8,0x00b70d54,0x3ee7e0bb,
    0x104febce,0xdddffddd,0x22005ddd,0x002f800f,0x02e403f3,0x01741f30,
    0x06b80d70,0x7c42e400,0xfd86a801,0x02e44eef,0x70001740,0x003fdddd,
    0xc817e664,0x01bd102f,0xf30d7bd1,0xf837d401,0x04f981fe,0x880004c8,
    0x003d800f,0x03e403f5,0x004d8f50,0x00d701b6,0x2e41f880,0x4fa86a80,
    0x32000f60,0x0fc00004,0x801ff900,0x805e80fb,0x209d06fe,0x3ff07bf9,
    0x26403640,0x007c4000,0x7ec0075c,0x400bf201,0x4007dc4e,0x035c06f9,
    0x3f12e400,0x7f71aa00,0xb8002f80,0x01e66445,0xfc8007e0,0xfa8bd002,
    0x106f8800,0xf8bfa89f,0x7c402f81,0x00026400,0x4e8007c4,0x900ffdc0,
    0x0fc801ff,0x7f4405e8,0x00035c06,0x005c8fc4,0x802fc9aa,0x45b8002e,
    0x4002fffa,0x01f2001f,0x002646a8,0x77fcc0db,0xf01f14ff,0xc803f003,
    0x0f880004,0x901bf300,0x66403f3f,0x2fd883fc,0xd303df10,0x06b80d7b,
    0x3f1b9000,0x76c75400,0x0007b001,0x05ffc899,0x32001f80,0xe83e6005,
    0x201ae002,0xf83541b9,0x6401f801,0x0f880004,0x37bfa200,0x01f88efe,
    0x6f7fd532,0x6c400efe,0x54ffddef,0x0006b80d,0x800bbf10,0x2005fefa,
    0x42e8005c,0xf8000fff,0x80172001,0x8007e0f8,0x16e0006b,0x00fc00fc,
    0x22000132,0xcb98000f,0xc807e21b,0x00de5cc4,0x82af2a60,0x0035c06a,
    0x8003f900,0x004e9dfa,0x0f8800d7,0x4000ffe6,0x01b2001f,0x001ec798,
    0x1f4000d9,0x01f801f8,0x44000264,0x4400000f,0x0013201f,0x80d50000,
    0x3200006b,0x226a8006,0x03f8804f,0x0df91b20,0x9000fc00,0x71ae001f,
    0x0037400b,0x03f00fc8,0x04c803f0,0x000f8800,0x9007cc00,0x80000009,
    0x0035c06a,0x8002f880,0x4027cc6a,0x1f9800fa,0xf00017f4,0x027e4003,
    0x07e617c4,0x2001bea0,0x007e02f9,0x0099007e,0x0001f100,0x26406c80,
    0x2a000000,0x400fcc06,0x80036400,0x804f986a,0x0be601ee,0xf8000bf1,
    0x0bfb2001,0x1d705d88,0x00377cc0,0x03f013ee,0x04c803f0,0x000f8800,
    0x900bea00,0x80000009,0x0aee806a,0xf1027e4c,0x41aa0005,0xbfd804f9,
    0x0c13ee20,0x400fc000,0x0df9cea9,0xf9007754,0x557dc415,0x44110aaf,
    0x2ea02fda,0xfba80abf,0xb55510ab,0x0355555d,0x3eeaaaa6,0x201aaaab,
    0xfdbaaaa8,0x2b7aa603,0x800000aa,0x0aafcaaa,0xffdffb10,0x555445df,
    0x000aafda,0x3220d953,0x3ee01acf,0x002dffef,0x75555300,0x4355557f,
    0xfd34fff8,0x2009ffdf,0x2efeefeb,0x3ee5fff5,0x200cefff,0x42fffff9,
    0x72fffff9,0xffffffff,0xffd01fff,0xffffffff,0x3fee01ff,0x2201deff,
    0x3fffffff,0x7fcc0000,0x402fffff,0xf701aba8,0x7fffffff,0x41bffa00,
    0x807ffffc,0x800002a8,0xfffffffe,0x000fffff,0x00013551,0x44001551,
    0x000000aa,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0xdb730000,0x5530007b,0x00173001,0x33333330,
    0x2e200333,0x730001ab,0x33330035,0x06666603,0x006f2ea2,0x201aca98,
    0x99999998,0x20999999,0x99999999,0x26666000,0x26666009,0x00666209,
    0x99881333,0x204ccc01,0x99999998,0xcffb8000,0x1001eeca,0x32603fdf,
    0x64000ffe,0xffffffff,0xfd9103ff,0x793dffdd,0x777fecc0,0x7e4793ff,
    0x7e45ffff,0xfb35ffff,0x03dfdbdf,0x7ff77f4c,0x3ff62d9e,0xffffffff,
    0xfff76fff,0x9fffffff,0x7fffe401,0xffffb05f,0x3fffeabf,0x5ffffb05,
    0x417fffea,0x3a2ffffd,0xffffffff,0x40bf2000,0xf6c800fc,0x9beff983,
    0x9998000f,0x0199dd99,0x4c415bd1,0xbf104ffc,0x89ddd503,0x33019cd9,
    0x416fc3d9,0xcf980fd8,0xb1ffed40,0x5f533339,0x4cd93333,0x99999af9,
    0x36601ffd,0x2660099d,0x3f2209ec,0x2067cc01,0x74c01ee8,0x7cccc40e,
    0x2200099a,0x202f403f,0xa883f2f8,0x00003e20,0x13a2026c,0x3a213e60,
    0xd84fe803,0x1f8d7004,0x17e17e20,0x41ec7fb0,0xf86b80f8,0x803f6201,
    0x01f4007a,0x00eb809d,0x0fb807f1,0x90001f80,0xd80f500b,0x3e2007e5,
    0x09b00000,0x136006e8,0x27cc017a,0x46b8026c,0x263e400e,0xb1fc401f,
    0xd701f107,0x4f8803f0,0xf98017c0,0x4c07e600,0x80fd402f,0x03f002f9,
    0x22002600,0x7c1f300f,0x000f8801,0x7c409b00,0xf3066000,0x6c1ec001,
    0x000d7004,0x803d43f1,0x3e20f62c,0x01f86b80,0x02e405c8,0x06c805d8,
    0x03ee00bd,0x0fc007f1,0x3e600000,0x01f89d00,0x00000f88,0x0035409b,
    0x02002dc0,0x06b8026c,0x3e60f980,0x883d8000,0x1f86b80f,0x7cc04c80,
    0x800fc400,0x0007dc4e,0x4005e8db,0x4000001f,0xf81f705d,0x000f8801,
    0x26c09b00,0x001ec000,0xd7004d80,0xbd0bb000,0xf1013000,0x03f05101,
    0x3e801f88,0xf30035c0,0x1000be23,0x0003f29d,0x4000003f,0x83f881fa,
    0x00f8801f,0x7c09b000,0x02f80002,0x2009b000,0x3f62006b,0x01bee881,
    0x0007c400,0x02fdc03f,0x01f406a8,0x002edb20,0x001fcf98,0x000001f8,
    0x41b205f5,0x00f8801f,0x7c09b000,0x01f80001,0x2009b000,0xdfc9806b,
    0x77fed400,0x3e2000ac,0x2ab3e000,0x004ffdba,0x00f980fc,0x007f7440,
    0x0007f700,0x2000007e,0x03f303fa,0x03e2007e,0xf026c000,0x03f00003,
    0x40136000,0x0efd406b,0x7fe5cc00,0x001f1001,0x7f77777c,0x05c8000d,
    0x3ea000b9,0x77f40003,0x001f8000,0xb01fd400,0x4400fc0b,0x401a600f,
    0xf80be04d,0x26ffffff,0x9b00002f,0xf501ae00,0x17e40000,0xf0007c40,
    0x003fd883,0x02f80f98,0x0003f100,0x002f4764,0x800c00fc,0x03ea03fa,
    0x0f8801f8,0x26c01ea0,0x4cc407b0,0x13a0dd99,0x8026c000,0x0034c06b,
    0x22017200,0x407e000f,0x3e8003fb,0xf10003d4,0x47ea0003,0x0fc003f8,
    0x3ee00fc0,0x7777e402,0x0defeeee,0x7a803e20,0x2e409b00,0x0b913600,
    0x40132000,0x1800805c,0x2201e600,0x807e000f,0x35c002f9,0xf8800136,
    0x42f98001,0x07e001fa,0x2fb807e0,0xccccca80,0x403dfccc,0x01ea00f8,
    0x01f501fc,0x0be226c0,0x401aa000,0xf880004e,0x801f3001,0x07e000f8,
    0x44001f90,0x0003f11f,0x22000fc4,0x001f904e,0x407e007e,0x200002fc,
    0x00f8801f,0x07e601ea,0x26c00bd0,0x6a8007e4,0x7c401f88,0x5f880002,
    0xf100d700,0x400fc001,0xba6c004e,0x0fc40006,0xbb01b600,0x3e007e00,
    0x0001fc81,0x7c400fc0,0x8813e600,0x04f8805e,0x03b609b0,0x3b607f90,
    0x980bd100,0x3fe203ed,0x401fc402,0x07e000f8,0xa8007e60,0x880007d7,
    0x03ee001f,0x3f009f10,0x1fd83f00,0x0fc00380,0x26007c40,0x3f6609ee,
    0x15dd3000,0x7409f930,0x3f6a20bf,0x26176c02,0x7ff400fe,0x7fbf102f,
    0x540bf701,0x2aabfbaa,0xaacfaa88,0x002bb200,0x40007efc,0xaabfbaa9,
    0x35bf5102,0x82ff2a60,0xaacfaaa9,0x1fbaaaaa,0x2aaab3ea,0x01fbaaaa,
    0x20e7d54c,0xabfbaaaa,0xffc80aaa,0x8000dffe,0xffeefffc,0xfffb802d,
    0x9000dffe,0x01bffdff,0x403fffb0,0xfeffe98e,0x3fe603ff,0x1fffffff,
    0x7fffffdc,0x013fe202,0x4c002fe4,0xffffffff,0xffffc81f,0xbffffd07,
    0x7ffffff4,0xffffffff,0x3ffffea1,0x1fffffff,0x3ffffe60,0xfffff30f,
    0x05ffffff,0x0000554c,0x004d5d44,0x000d5440,0x80015530,0x544001aa,
    0x000009ab,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x20266666,0x98809998,0x33100999,0x99988133,0x80999999,0x33301999,
    0x33333103,0x33100133,0x33333333,0x4ccc1333,0x99999999,0x4ccc4199,
    0x33000999,0x33333333,0x99999983,0x33100099,0x19999803,0x88004cc4,
    0x26660099,0x20000999,0x8809acc8,0x3ffee00a,0x7ff43fff,0x3ffea3ff,
    0xfff80fff,0xfff52fff,0xffffffff,0x37fffe45,0x89bffff2,0xffffffff,
    0xffa81dff,0xffffffff,0xff75ffff,0xffffffff,0x7fdcffff,0xceffffff,
    0xfffff102,0x21ffffff,0xfffffffb,0xf101dfff,0x3f205fff,0xff35ffff,
    0x3ff600ff,0xffffd83f,0xfb0006ff,0xfa83ffbb,0x3e6602ff,0xdfa8809b,
    0x099bf880,0x81f53310,0x9af99998,0x1bf98099,0x3105f330,0x533333bb,
    0x7f3109f9,0x33333333,0x57cccbb3,0x99999999,0x4cee447b,0x84fca999,
    0x99999af8,0x2660fb99,0xb99999af,0xfb3103fe,0x0fdccc0d,0x300ff762,
    0x4cc01d9f,0x001fafa9,0xb01107d4,0x3f00dfff,0x3e027cc0,0x403d4002,
    0x03f000f8,0x02e403f0,0x01740bea,0x801f85c8,0x4c05c87a,0x100fc44e,
    0x7007e09d,0x2766403f,0x5e641aa0,0x0356e406,0x00136b90,0x3fee007b,
    0x501f804f,0x107d007f,0x100d7013,0x007e001f,0x805c807e,0x2005d07d,
    0xa801f85c,0xf9805c87,0x6d807e21,0x13a007e0,0x200facc8,0x3f19906a,
    0x01aa7e20,0x800f52f8,0x2f6e002f,0xfb81f800,0xfb09b003,0xf100b909,
    0x2007e001,0x2017201f,0x002e80f9,0x3003f099,0x3200b90d,0x7d407e26,
    0x2e007e00,0x02ed3206,0x2e5320d5,0x200d56b8,0xb0017c7a,0x7c000009,
    0x90017e41,0x990fbf0b,0x2001f100,0x201f801f,0x81f8805c,0x3e00182e,
    0x5c808181,0x06c3f100,0x07e01fc4,0x14c81360,0x641aa05f,0x27d01f14,
    0xc89b006a,0x003e6005,0xf90fc000,0x4c6b8003,0x01ec1f9f,0x1f8007c4,
    0x17201f80,0x41741ea0,0xf03f002e,0x400b9003,0x805e803e,0x00fd401f,
    0x6a836499,0x2a26c990,0x3e201aa7,0xb0007cc1,0x3e00000b,0x50005fb1,
    0xe87d6b8f,0x000f8802,0x403f003f,0x827cc05c,0xf002f82e,0xb9003f03,
    0x2e026400,0x981f800f,0x26402fda,0x641aa0fa,0x24d83ea4,0xd06a806a,
    0x0bff2007,0x3abe0000,0x4c003fee,0x7c6ba747,0x000f8801,0xffffffff,
    0x2e403fff,0x3a05fb88,0x02ffffff,0xfffffff0,0x400b9003,0x00be605c,
    0x7ffffffc,0x44c805ff,0xc83540fa,0x20f99f44,0x703d806a,0xb9ee880d,
    0x0002fdc6,0x1bee1bff,0x3f10f880,0x007c43e6,0xbf8007c4,0x99999999,
    0x3bbf201f,0x403ffeee,0x2f9999be,0x33335f00,0x00b9003f,0x009d02e4,
    0x54cccd7c,0x3201eecb,0x83545d84,0x45cb5c4c,0x807c406a,0xd1aa01f8,
    0x7b506749,0xd30bf001,0x7a8fc009,0x1007997c,0x007e001f,0xccec807e,
    0xe800abcc,0x3f002f82,0x0b9003f0,0x06c826c0,0x7e400fc0,0x3f309902,
    0xf84c8354,0x203541fa,0xaaaaaafb,0x313604ea,0x7dc3f13f,0x01f804ff,
    0x4ba005f1,0x07aa645c,0x3e001f10,0x3201f801,0x41740005,0x703f000a,
    0xf8017200,0x7301fa82,0x172003f0,0x2a6c8264,0xdf709906,0xffe80d50,
    0x7fffffff,0x2fb20be0,0x037ffec5,0x00d900fc,0x5ea1f4f6,0x01f1006a,
    0x07e007e0,0x740005c8,0x00fc0002,0x802e43b8,0x01fc40f8,0x2003f0d7,
    0x104c80f9,0x2641aa7f,0x03541644,0x05f001f3,0x0bfe213a,0xf007fff5,
    0xd802f803,0x4fc40f9c,0x01f1005b,0x07e007e0,0x740005c8,0x00fc0002,
    0x802e44c8,0x5c05d86c,0xf1001f86,0x7d409901,0x009906a8,0x017206a8,
    0xb07c82e4,0x0035101f,0x00d9007e,0x2fa0d799,0x01f1004c,0x07e007e0,
    0x740005c8,0x00fc0002,0x402e44c8,0x007dc0fb,0x4007e1ae,0xe809906b,
    0x009906ac,0x00be06a8,0x6fc407cc,0x15bdf912,0x200fc000,0x6edc01f8,
    0x007bb704,0x0fc003e2,0x0b900fc0,0x0002e800,0x44c800fc,0x20fdc05c,
    0x86b802f9,0x03fa801f,0x6cf98099,0x6a800990,0x3e800f50,0x3ffdfd10,
    0x8800bff1,0x00aacfaa,0x3ea035bb,0x05df302f,0x2feeaaaa,0x2a60aaaa,
    0x55440acf,0x36a60acf,0x401aaaae,0xaaacfaa8,0x7d54400a,0xaaaaaaac,
    0xdb514eaa,0xffb55555,0x5555db05,0x2d955555,0xaaacfaa8,0x83fdbaaa,
    0x00aadda8,0xdda88df9,0x955100aa,0x376a215f,0xb55100aa,0x06a6015d,
    0x7ffdc000,0xff502fff,0x01ff301f,0x7fcc0ffc,0xffffffff,0xfffff32f,
    0xfffffb8b,0xffffff13,0xffa80dff,0x04ffffff,0x7fffffdc,0xffffffff,
    0xffffff54,0x36015bff,0xffffffff,0xfff76fff,0xdfffffff,0x3ffee039,
    0x8df105ff,0x05fffffb,0x2bfffff7,0x05fffffc,0x0bfffff9,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0xbdb95100,0x65c40017,0x20063cee,
    0x01bdedca,0x37bdb730,0x01555540,0x440aaaaa,0x451cdeda,0x5500aaa8,
    0x55530155,0xaaaa8815,0x55555541,0x220aaaaa,0xcc982aaa,0x710aa981,
    0x980059db,0x26aaa600,0x000000de,0x2003f220,0xefe8800f,0x02ffdbbc,
    0xecbcefa8,0xb101faff,0x7fd979bf,0xcacefb80,0xdffb04fe,0x7ff6c01d,
    0x37ffa20e,0x50feffdb,0xdd105fdd,0xdff703fd,0xffee985d,0x777777c4,
    0x2a1ffeee,0x3fa67eee,0x7f6c4fcd,0xfebcefaa,0xa8132005,0xcfd9bfff,
    0x5c000000,0x0f8802ef,0x7e401500,0x440fee00,0xdf981ffb,0x360bd500,
    0x20dd302f,0x41ec005b,0x1fd301fd,0x03f005f0,0x1d9017a2,0x1fcc03f0,
    0x837eaf50,0x2fef80d8,0x9b004f98,0x517ffcc0,0x000007fd,0x44007fd5,
    0xf100000f,0x200be207,0x805e81fd,0x007dc2f9,0x01e613e2,0x805f05f0,
    0x802f80fa,0x417a201f,0x203f00ed,0x67d404e8,0x0ffc002f,0x13600f90,
    0xb81fff88,0x980002ef,0x44000cfd,0x3600000f,0x2200bb04,0x5003dc1f,
    0xa8017c4f,0x7d41f81f,0x2f407c43,0x802f81c0,0x06f4401f,0x881401db,
    0x1ffa805e,0x4403f800,0x9b055c1f,0x0fff1d44,0x000f7e44,0x0006fe44,
    0x88000f88,0x209b0999,0x3602001f,0x6a8fc004,0x1f41f400,0x20d51bf6,
    0x4000acfa,0x801f802f,0x00ed8ee8,0x2a00db00,0x05f0000f,0xdffc83f0,
    0x4ffdadda,0x36201ffa,0xdf7000df,0x0f880003,0xffff9100,0xf109ffff,
    0xeee80001,0xeeeeeeee,0x00b92fee,0x224c84c8,0x81720faf,0x2cefffd9,
    0x0fc017c0,0x001dfb00,0x54003b60,0x00be0007,0x7fed407e,0x6fd82cff,
    0x033f6600,0x000177d4,0xfa800f88,0x3aa609ae,0x80007984,0xccccccde,
    0xb2cccccc,0xa85b8009,0x7d1f5aa6,0x3fb2a200,0xf005f01e,0x3bfa2003,
    0x00fc8000,0xf8001ea0,0x5401f802,0x13f202ff,0xa8ffaa00,0xd50003fe,
    0xddfddddd,0x3e67dddd,0xf884d804,0x026c0000,0xd800b700,0x29b0f884,
    0x40007e6b,0x02f81fc8,0xde8801f8,0x2e000ed8,0x03d4001f,0x3f005f00,
    0x07e5fc40,0xa8003fb8,0x33f662ef,0xccc98000,0xcccdfccc,0x001f72cc,
    0x000be09b,0x54000d70,0xf817c007,0x33f11f8a,0x7400260f,0x1f802f84,
    0x3b62f440,0x002fa800,0x3e0007a8,0x3a01f802,0x06c417a5,0x407fd500,
    0x00003fea,0x04d801f1,0x0d904e88,0x01fc4280,0x32009d00,0x8d57b00e,
    0x09b06abd,0x00fa1720,0x2f4403f5,0x3e600ec8,0x3d40ee03,0xf005f000,
    0xf883ee03,0x7ecc0003,0x5df7000c,0x00f88000,0xff5007dc,0x2013e209,
    0x02fa86e9,0x0be62c88,0x6dc03f50,0x82675c4d,0x1fcc00ed,0x3ff702dc,
    0xf9017a20,0xd807f103,0x4000f504,0xb01f802f,0x2000b503,0x8000dfc8,
    0x0001efc8,0xdf8801f1,0x373f2621,0x1ef981ad,0x8077e4c4,0xfc981dfb,
    0x20efdc1e,0x7cc03fd8,0x817fc41f,0xea80affd,0x2217f106,0x41cfafda,
    0xa80aafe9,0xdd10afea,0x55555555,0x7dcccc9d,0x00aaaaaa,0x30159f53,
    0x000039f5,0x003df700,0x01bfb100,0x9800f880,0x1effeffe,0xb101fffb,
    0x5bffddff,0xddffd100,0x74405dff,0x01effeff,0x1fb06f88,0x3ffeef20,
    0x200cffee,0x0dffefeb,0x3fe61fff,0x7fcc2fff,0xfff52fff,0xffffffff,
    0x3ffffe69,0x83ffffff,0x83fffff9,0x000ffffe,0x05df5000,0x9fd30000,
    0x003e2001,0x0009ba98,0x026ae620,0x06ae6200,0x01555100,0x4c000000,
    0x20009aba,0x000001a9,0x00000000,0x00000000,0x00ffa600,0x3faa0000,
    0x000f8802,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00067400,0x03ae0000,0x551003a0,0xc88b76e3,0x555500be,
    0xaaa88155,0xccc882aa,0x33066624,0x88038013,0x88888888,0x20088888,
    0x005c001a,0xffff87b5,0xffffffff,0x9999950f,0x99999999,0x00079999,
    0x00000000,0x00000000,0xfd700000,0x35fb9ddb,0x360fd7df,0x4c2eeefe,
    0xa85efeee,0x3ff63fff,0x0dfff10f,0xff3027dc,0xffffffff,0x985fffff,
    0x8300dfff,0xfffb80ed,0x3fffffe3,0x0fffffff,0xbbbbbbb5,0xbbbbbbbb,
    0x000019bb,0x00000000,0x00000000,0x3bf60000,0x5d13fee0,0x5d802e40,
    0xc83fff20,0x2fffc7ff,0x202fbfa8,0x99999998,0x41999999,0x81dd13fa,
    0x6c1fd87b,0x00005fff,0x00000000,0x00000000,0x00000000,0x3f600000,
    0x35c2fc40,0xf8803f10,0x70fffe01,0x3ffe8dff,0x03f73f88,0x43f80000,
    0x2fb89ed8,0x7fd45f90,0x0000002f,0x00000000,0x00000000,0x00000000,
    0x7c136000,0x26c06a81,0xff981b20,0x6c5ffa86,0x645e82ff,0x2000000e,
    0x077fee00,0x05c41f70,0x00000000,0x00000000,0x00000000,0x00000000,
    0x40fc1360,0x007cc06a,0x17fdc05f,0x3ee27fcc,0x74076c1f,0x55555445,
    0xaaaaaaaa,0x022000aa,0x00000000,0x00000000,0x00000000,0x00000000,
    0x13600000,0x403540fc,0xd80f503e,0x87ff106f,0x03ee0ffa,0xddd327c4,
    0xdddddddd,0x0003dddd,0x00000000,0x00000000,0x00000000,0x00000000,
    0x9b000000,0x01aa07e0,0x201f41ea,0x07fe02ff,0x017ccff3,0x000007e6,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x503f04d8,
    0xf30be00d,0x202fcc01,0x12fc40fd,0x0002a005,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x3f04d800,0x1ae00d50,0x8038809b,
    0x00013018,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x36000000,0x0d503f04,0x0fc47e20,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x20000000,0xd503f04d,0x05cae400,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x22000000,0x67c0adea,0x40057d41,0x0002fbf9,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x3fee0000,0x07ffc2ff,
    0x3600bff5,0x0000006f,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,
};

static signed short stb__courier_36_usascii_x[95]={ 0,7,4,2,3,2,3,7,9,4,0,2,4,2,
7,3,3,3,2,3,3,3,4,3,3,4,7,4,0,1,0,0,3,0,1,1,2,1,2,1,1,3,2,1,
1,0,0,0,2,1,1,2,2,1,0,0,1,1,3,0,0,0,3,1,6,2,0,2,1,1,3,1,1,2,
2,2,2,0,1,2,0,1,2,3,2,1,0,0,1,2,3,0,8,0,2, };
static signed short stb__courier_36_usascii_y[95]={ 26,6,6,5,4,6,9,6,6,6,6,8,21,16,
22,4,6,6,6,6,6,6,6,6,6,6,12,12,8,13,8,7,5,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,4,6,6,33,5,12,6,12,6,12,6,12,6,5,
5,6,6,12,12,12,12,12,12,12,7,12,12,12,12,12,12,6,6,6,14, };
static unsigned short stb__courier_36_usascii_w[95]={ 0,5,11,15,13,15,13,5,6,6,12,15,8,15,
5,13,13,13,14,13,13,13,13,13,13,13,5,8,16,17,16,12,13,19,17,17,16,16,16,17,17,13,17,18,
17,19,18,16,16,17,18,15,15,17,19,19,17,17,13,6,12,6,13,20,7,16,18,16,18,16,15,17,17,15,
11,17,15,19,17,15,18,18,16,13,15,17,19,19,17,17,13,7,3,7,15, };
static unsigned short stb__courier_36_usascii_h[95]={ 0,21,10,24,25,21,18,10,25,25,12,17,10,2,
5,25,21,20,20,21,20,21,21,21,21,21,15,18,17,7,17,20,24,19,19,20,19,19,19,20,19,19,20,19,
19,19,19,20,19,23,19,20,19,20,19,19,19,19,19,25,25,25,9,2,6,15,21,15,21,15,20,20,20,21,
27,20,20,14,14,15,20,20,14,15,20,15,14,15,14,20,14,25,25,25,6, };
static unsigned short stb__courier_36_usascii_s[95]={ 150,208,100,116,47,150,231,250,82,33,237,
35,91,174,168,61,166,30,1,180,16,194,214,242,228,55,245,244,18,126,1,
116,102,211,154,80,123,106,89,62,54,40,44,1,236,191,172,227,72,132,161,
129,145,98,180,20,218,200,140,75,89,40,112,190,160,51,17,68,36,85,87,
119,69,1,1,209,103,51,219,102,137,156,202,138,175,152,71,118,170,191,188,
25,21,13,144, };
static unsigned short stb__courier_36_usascii_t[95]={ 23,1,108,1,1,1,72,92,1,1,92,
92,108,108,108,1,1,51,51,1,51,1,1,1,1,29,72,29,92,108,92,
51,1,72,72,51,72,72,72,51,72,72,51,72,51,72,72,29,72,1,51,
51,51,51,51,72,51,51,72,1,1,1,108,108,108,92,29,92,29,92,29,
29,29,29,1,29,29,108,92,92,29,29,92,92,29,92,108,92,92,29,92,
1,1,1,108, };
static unsigned short stb__courier_36_usascii_a[95]={ 305,305,305,305,305,305,305,305,
305,305,305,305,305,305,305,305,305,305,305,305,305,305,305,305,
305,305,305,305,305,305,305,305,305,305,305,305,305,305,305,305,
305,305,305,305,305,305,305,305,305,305,305,305,305,305,305,305,
305,305,305,305,305,305,305,305,305,305,305,305,305,305,305,305,
305,305,305,305,305,305,305,305,305,305,305,305,305,305,305,305,
305,305,305,305,305,305,305, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_courier_36_usascii_BITMAP_HEIGHT or STB_FONT_courier_36_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_courier_36_usascii(stb_fontchar font[STB_FONT_courier_36_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_courier_36_usascii_BITMAP_HEIGHT][STB_FONT_courier_36_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__courier_36_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_courier_36_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_courier_36_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_courier_36_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_courier_36_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_courier_36_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__courier_36_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__courier_36_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__courier_36_usascii_s[i] + stb__courier_36_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__courier_36_usascii_t[i] + stb__courier_36_usascii_h[i]) * recip_height;
            font[i].x0 = stb__courier_36_usascii_x[i];
            font[i].y0 = stb__courier_36_usascii_y[i];
            font[i].x1 = stb__courier_36_usascii_x[i] + stb__courier_36_usascii_w[i];
            font[i].y1 = stb__courier_36_usascii_y[i] + stb__courier_36_usascii_h[i];
            font[i].advance_int = (stb__courier_36_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__courier_36_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__courier_36_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__courier_36_usascii_s[i] + stb__courier_36_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__courier_36_usascii_t[i] + stb__courier_36_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__courier_36_usascii_x[i] - 0.5f;
            font[i].y0f = stb__courier_36_usascii_y[i] - 0.5f;
            font[i].x1f = stb__courier_36_usascii_x[i] + stb__courier_36_usascii_w[i] + 0.5f;
            font[i].y1f = stb__courier_36_usascii_y[i] + stb__courier_36_usascii_h[i] + 0.5f;
            font[i].advance = stb__courier_36_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_courier_36_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_courier_36_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_courier_36_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_courier_36_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_courier_36_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_courier_36_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_courier_36_usascii_LINE_SPACING
#endif

