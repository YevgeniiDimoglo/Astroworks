// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_times_31_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_times_31_usascii'.
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

#define STB_FONT_times_31_usascii_BITMAP_WIDTH         256
#define STB_FONT_times_31_usascii_BITMAP_HEIGHT        120
#define STB_FONT_times_31_usascii_BITMAP_HEIGHT_POW2   128

#define STB_FONT_times_31_usascii_FIRST_CHAR            32
#define STB_FONT_times_31_usascii_NUM_CHARS             95

#define STB_FONT_times_31_usascii_LINE_SPACING          20

static unsigned int stb__times_31_usascii_pixels[]={
    0x98000cc0,0x04c000aa,0x0c400540,0xfb000840,0x3fe3ffff,0xb8807fff,
    0x001bdeec,0x0000a800,0x02880031,0x32e000a8,0x66444ccc,0x765c403c,
    0x20001bde,0x1bdeeca8,0x4c0a8037,0x1013623e,0x36a003ff,0xbddbaabc,
    0x006e4400,0x066c405b,0x03225910,0x43337fb0,0x407f9999,0xeb99adfb,
    0x0064004f,0x0f200079,0x883fecc0,0x22001ffb,0xf880dffd,0x2b7ee00d,
    0x004fca88,0x44567f54,0x881fffb9,0x3fec0ffc,0x7c405ff7,0x05f5c01f,
    0x2600fa60,0x2605b01f,0x20f4c00f,0x0bf602d8,0xfd883fc0,0x003bf203,
    0x8179df95,0x01d00059,0x20ffb510,0x8001ffcb,0x01f104fe,0xfa80ffa2,
    0x0efc801e,0x2e0bfa20,0x7ff40ffc,0x8801df30,0x0006ec00,0x0db009d1,
    0x202740b6,0x40ba01e8,0x0ff002fd,0x3f6017f6,0x5b7dd106,0x00f87ff9,
    0x2a0034c0,0x00ffc07f,0x5b83fd40,0x32013f60,0x077e406f,0xf881fc40,
    0x007fec0f,0x013a2000,0x2e016c40,0xfa82d81f,0x26027403,0x002fd80f,
    0x03ff50ff,0xf909ff10,0x22f44321,0x01e4003c,0xff01fe60,0x0ffa0003,
    0x07fdc0ba,0x9827fc40,0x0f2002ff,0x3f207fc4,0x5d800007,0x6c068000,
    0xfc82d83f,0x2007f204,0x002fd85d,0x05ff88ff,0xf887ff60,0x4c598325,
    0x00074005,0x3ff01fe6,0x31bee000,0x017fe20d,0xfe81ffc8,0x881c4006,
    0x037dc0ff,0x003ee000,0x74019002,0xfb82d83f,0x200df105,0x017ec2fb,
    0x1ffdc7f8,0x549ff500,0xf0b0326f,0x001a6001,0x3ff01fe6,0xb17fc000,
    0x00ffea07,0x7c44ffa8,0x2200003f,0x02fd40ff,0x3e20da80,0x3736e202,
    0x80aa0fe8,0xa82d82ff,0x007f906f,0x05fb1be2,0x5ff91fe0,0x32ffcc00,
    0x030323ff,0x00f20079,0xff35bb93,0xdb51ff80,0x2df70019,0x5ff900f8,
    0x22ffcc00,0x00002ffa,0x9f503fe2,0x1fffc800,0x23e881ae,0x02445fd8,
    0x305b01ff,0x007fe0ff,0x0bf61fe8,0x3ffa3fc0,0x1ffe2001,0x00193fff,
    0x803a00d3,0xffd88cfa,0x7e4ffc07,0x4401ffff,0x3605baff,0x3e2001ff,
    0x00ffe47f,0x26666662,0x2607fc40,0xff98004f,0x85e80fa1,0x360583fe,
    0x9f105b07,0x4001ff50,0x00bf63fe,0x03ffe3fc,0x5c1fff00,0xf000efff,
    0x2a069801,0x407fe82f,0xfd99cdff,0x77e400ff,0x03ffe01e,0x741fff00,
    0x75c400ff,0x7c42efff,0x001fc40f,0x0f98ffc4,0xff881fb0,0x03ea0680,
    0x207e20b6,0x7ec007fb,0x7c00bf64,0x000fff47,0x3fee1ffe,0x03c800df,
    0x06f881e4,0x3ff80ff7,0x4403ffa8,0x7ff406ff,0x23ffc001,0xf1002fff,
    0x03fe20ff,0xf00570be,0x7dc1ea3f,0x4886f983,0x416c1ec0,0x00ff904c,
    0x0bf66fc8,0x3ff23fc0,0x1bfe2002,0x00f7ff4c,0x201f01a6,0x0ff304fb,
    0xbfd01ff8,0xd807f900,0x3e2002ff,0x027fec6f,0x3e20dff0,0x3ee1e80f,
    0xb8ffc01f,0xf706f886,0x95005509,0x039316c3,0x320037ec,0x400bf67f,
    0x01ffdc7f,0xe80bff30,0x07c03fff,0x0ff60698,0x3fe03fcc,0x300df701,
    0x3ffc801f,0x913fe600,0x7fc00bff,0xb01ff105,0x2007fd41,0xf50b91ff,
    0x320bfa09,0x96cd7001,0x37ec03e8,0x6c3fee00,0x98ff002f,0x3ea004ff,
    0x7fde402f,0x640f203f,0x4c0ffe03,0x80ffc07f,0x04b807fa,0x2004ffa8,
    0x7fd42ffa,0x417fe007,0x98480ff8,0x991ff800,0xff703f90,0x072201a0,
    0x900ca85b,0x7fb800df,0x3fc00bf6,0xfb003ff4,0xfd11900d,0x0f834c0d,
    0x7cc13fe0,0xa80ffc07,0x001e806f,0x36001ffb,0x05ffb06f,0x7c417fe0,
    0x7c00000f,0x0ff0b71f,0x0790bfd1,0x82d82f88,0x07fa80fb,0x5fb37e40,
    0x3e21fe00,0x2ff9803f,0x3ff10c80,0x01a60740,0x1fe60bfd,0x3ee03ff0,
    0x3002dc04,0xff3007ff,0x07ffe603,0x7c417fe0,0x0373000f,0x88d51ff8,
    0x3ef620ff,0x3dc03543,0x83f882d8,0x36000ff9,0x400bf65f,0x01ff507f,
    0x40a83fd8,0xc80ff60c,0x3f601e43,0x407f980f,0x83fb01ff,0x000eabdb,
    0xd1007fdc,0xeff9807f,0x882ffc00,0x20dc40ff,0x8ffc06fe,0xa8cfe878,
    0x3a63fc8d,0x407f40a0,0xf06f882d,0x27f4001f,0x1fe005fb,0xe881efb8,
    0x0c87703f,0x46980bf6,0x2ffcc00f,0x3fe03fd4,0x7c44f881,0x50002fff,
    0x5fd303ff,0x0bbf6200,0xf8827fcc,0x363fec1f,0xb0ffc05f,0x0dfffb85,
    0x419b7df5,0xb03ff049,0x3a0ff505,0x83fe001f,0x0ff002fd,0xeccefc88,
    0x91ae00cf,0x3a007fc1,0x3f200d30,0xffed9adf,0x41dfd03c,0x3bf706ea,
    0xefd88000,0x000dfecc,0xccdffdb8,0x3e601dfe,0x0c37e42f,0x0b50ffc0,
    0x03730173,0x417f4036,0x506fb82d,0x17e6009f,0x1fe005fb,0x27fff440,
    0x0c8e7dc0,0x279003fb,0x3fee003c,0x0bef9bff,0xfbbff910,0x00000007,
    0x00001551,0x400cd4c4,0x20ceffeb,0x1ff00009,0x500002e8,0x6c1fec09,
    0x3604fc82,0xd83f9006,0x00ff002f,0x402fffd8,0xfdeeffc9,0x2a31000d,
    0x10998000,0x01a98005,0x00000000,0x00000000,0x0ff00000,0x980001d1,
    0x20bf200d,0x203fb82d,0x85f801f8,0x0ff002fd,0x03fff700,0x002ba660,
    0x00000000,0x00000000,0x00000000,0x00000000,0x07541be2,0x400da800,
    0x982d80fc,0x2035c03f,0x005fb06a,0x644001fe,0x032001ff,0x00000000,
    0x00000000,0x00000000,0x00000000,0x405f114c,0x322002e9,0x3609d005,
    0x7b00db02,0x7ec03a60,0x9990cccd,0x88000ff9,0x0400beeb,0x00000000,
    0x00000000,0x00000000,0x00000000,0x0b91bff0,0x837bd910,0x8801dc98,
    0x440b604c,0x544b803d,0x3332a00d,0x999990cc,0x29800009,0x00000000,
    0x00000000,0x00000000,0x00000000,0x3bfae000,0xfeda8003,0x5001cdee,
    0x402d8059,0x994401ca,0x00000002,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x4c000000,
    0x00660001,0x65400033,0x44000add,0xb099000a,0x37bb6a05,0x01f6dc02,
    0x332a0b70,0x9970cccc,0xc9839999,0x4400cccc,0x0000beda,0x98017bb5,
    0xca803dec,0x3004cccc,0x66445bb7,0x3ccccccc,0x66666644,0x9999913c,
    0x13faa599,0x20ffc400,0x0004feb8,0x3ffa63fb,0xd9b303ff,0x82d803bf,
    0x88aed80f,0x11db05ea,0x01d300bf,0x206fffcc,0x100dfffa,0xf8801bf9,
    0x001fc8ae,0x076c4ef4,0x5fffffe8,0x7fffffc0,0x80afc805,0xfffffffc,
    0xfff304ff,0x9fff503b,0x013feea1,0x2a0ffc40,0xb8004ffb,0x4cffd44f,
    0x3f61e880,0x1e207c06,0x0fee0bee,0x007e45f5,0x3fea00ba,0x807ff703,
    0x1fe800fa,0x1f900274,0x8e5c3fc4,0xd701ffea,0x403ddddd,0x3fe00ee9,
    0xfdccccde,0x807ff201,0x4fd80ffd,0xe8022000,0x2ff8004f,0xdd017fc4,
    0x1e206e88,0x441fa16a,0xf50fec6f,0xf0026405,0x17fe20bf,0xff300990,
    0x3ea00d90,0x0e63fb83,0x07c13fe2,0x501be600,0x6406d80d,0x1ff600ff,
    0x000027ec,0x88009fb0,0x04fe82ff,0xb5000df1,0x01ff0790,0x21fe8df1,
    0x01d304fa,0xd807fe40,0x400f407f,0x004f87fa,0x4ff303ff,0x2e0ff600,
    0x0ffc4004,0x09f00320,0x7e407fb8,0x0009fb07,0x0027ec00,0x27ec27f4,
    0xc8005f98,0x4fe82e84,0x0ffc3fa8,0x007a0df5,0x2a05ff30,0x00f302ff,
    0x0fb8bfe6,0xf107f980,0x03f9007f,0x360015bf,0xfa80003f,0x203fdc01,
    0x09fb07fc,0x27ec0000,0x7c37e400,0x00bf501f,0xdddfddd5,0x5c5ddfdd,
    0x03ba23ff,0x427d43fb,0xbff0004c,0x6417fee0,0x2bff1004,0xff5002fc,
    0x74027fc0,0xdffffb84,0x003fea00,0x2e01b200,0x83fe407f,0x666644fd,
    0x00db882c,0x33ae29fb,0xb8ff6201,0xefdcb83f,0x755304cc,0x5f75557f,
    0x8cffe835,0x22fb80de,0x0034c2fc,0xfd01ff90,0x003d01ff,0x706f7fec,
    0x7e4bffff,0x7017fa06,0x3ffff60b,0x2bfd02ff,0xf8003cb8,0x407fb804,
    0x89fb07fc,0xfc80aff8,0x19fb00ff,0x401fffdd,0x01ddeee8,0x555dfb55,
    0x0b50f300,0x027fff44,0x2237457a,0x3e60001e,0x7fd7c43f,0x2e003cc2,
    0x1df905ff,0x3f606fd8,0x01bf7106,0x17ffecc4,0x33337fe2,0xf5001eff,
    0x80ff7003,0x89fb07fc,0x7fd400ec,0x41bbfb00,0x007604fe,0x50017ee0,
    0xfd00790b,0x6e4403df,0x0104c82d,0x56e37f40,0x802645ff,0x81ffefc8,
    0x05fe81fb,0x3fea1ff6,0xfb801fff,0x0bfea0ff,0x3200dff1,0x80ff7006,
    0x49fb07fc,0x1ff1005c,0x3ee17f60,0x0001f906,0x3c800bf7,0x66dc02e8,
    0x50001fff,0x05dbd70d,0x9741ff70,0x007e0ffc,0x3fea3be6,0xbfd04e86,
    0xb3037ec0,0x3e600fff,0x541fee3f,0x04f803ff,0xfc80ff70,0x1769fb07,
    0xb00ff880,0x20df509f,0xeeeefffe,0x00bf701c,0x200f82e8,0x3fff70ec,
    0x541e8800,0x8803f51f,0x7ccf33ff,0xf300d33f,0x127fec1d,0x817fa01d,
    0xffb804fd,0x6c9fb001,0x0bff106f,0xf7001f98,0xb07fc80f,0x4001fb9f,
    0x9fb00ff8,0x3e60ff50,0xffffffff,0xb805fb84,0xffffffff,0x3ee3ffff,
    0x0027fd41,0xdf1be0f6,0x132dfd00,0x20132dfd,0x7ffcc2ff,0x37ec03d1,
    0x3a007fd0,0x4bf5003f,0x1bfa06fc,0x7dc00d90,0xd83fe407,0x4005ffdf,
    0x09fb00ff,0x45660ff3,0x0fdaa999,0x4c402fdc,0xdb9999fa,0x41fa0999,
    0x1aa007fb,0x01fd17e6,0x41e9ffb8,0x401f8ffb,0xffc80ff9,0x37dc04be,
    0x32005ff0,0xb93e004f,0x01bf607f,0x3fdc009f,0x7ec1ff20,0x2003ff9c,
    0x09fb00ff,0x01f10ff3,0x05fb83d0,0x40f216a0,0x07fa06f9,0x3ea03e20,
    0x2200ff45,0xff986eff,0x07fc806e,0x1003fffa,0x1ff101ff,0x400bea00,
    0x03fe62f9,0x3f3027e4,0x2037dc00,0x29fb07fc,0xff001ffb,0x2613f601,
    0x9806e87f,0x2005fb87,0x3e01e83c,0x003f900f,0xd17ea07b,0x9ffb003f,
    0x200fffa0,0xff102ffe,0x2fd8a09f,0x36005fa8,0xd0d9000f,0x807fa05f,
    0x2fdc006c,0x7ec1ff20,0x2003ff64,0x09fb00ff,0x19ff0ff3,0x3ee07a20,
    0x3e0ba005,0x740bf200,0x2205b806,0x4007fc5f,0xff701ffa,0x1bffb003,
    0x19ffff90,0xb0bf31d4,0x8fe2001f,0x81f880a8,0x05f886f9,0x4dd1027c,
    0x3fec02fc,0x3fa24fd8,0x80ffc406,0x87fa84fd,0xdcdefffa,0x0df901ee,
    0x01a607c0,0x1fa81df1,0x3a007c40,0xf8017e67,0x401be206,0xb9cffff9,
    0xffff98de,0x21fa86ee,0x0efe41fa,0xcffb87d7,0x3202fd99,0x803b223f,
    0x3fe601f9,0xfff00bb3,0xf98bfd03,0x5ff300df,0x3ee17fa0,0xffec880f,
    0x7fec03de,0x5a869800,0xebdfe880,0x802d801d,0x00ed8cf8,0x07b00f20,
    0x7ffff4c0,0x7fff442f,0xbbbd701d,0xdffff505,0xfffd103b,0xbb50019d,
    0x0f900bd9,0x019bffb0,0x3fffff22,0xcfffdbac,0x19dfff92,0x5277ff64,
    0x9159fffb,0x0007dfff,0x7ffffb50,0x0cc14403,0x40026600,0x32e2004a,
    0x40088001,0xaa980009,0x80054400,0x00988009,0x20001310,0x006a0018,
    0x00000144,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x80000000,0x21bdedb8,0x333332e5,0x3332e03c,
    0xcdec983c,0x6776cc00,0x37660b0b,0xccc983de,0xccca803c,0x999973cc,
    0x99501999,0x2e207999,0xc85a9ded,0xcccccccc,0x80cccccc,0x39d931d9,
    0x99999930,0xcccc8199,0x999951cc,0x20135799,0xccccccca,0xca8009aa,
    0x90003ccc,0x2e019999,0xfc98acfe,0x7ff547ef,0x3ee200af,0x45fdc0cf,
    0xbf901fea,0x0dffb735,0x3bf661b7,0x03fffa80,0x4c1dfc88,0x4402fffd,
    0xbf502efc,0xf0fff933,0xffd999df,0x43ffd999,0xffaaffeb,0xfb982fff,
    0xf500cfff,0xffc8819f,0x0dffecdf,0xccfffc88,0x8803fffd,0x4000fffc,
    0x880bfffa,0x3fd406fd,0xf0037fcc,0xf883f70d,0xc827dc0f,0x7407c46f,
    0x5fff104f,0x2a05f300,0x7f3004ff,0x3f20bea0,0x6fd82f87,0x7fc41f98,
    0xfffd99db,0x07fff300,0xff101fcc,0x82ffe88b,0x7e445ff8,0xfff8806f,
    0x37ff4004,0x7001ffb0,0x01ffd01f,0x5f883f30,0x0ff89f90,0x05f71b20,
    0x7fec0ff9,0x301f800f,0x0fc007ff,0x7fa82fc4,0x06fd82c4,0x70bff057,
    0x7fcc07ff,0x3e013a06,0x06ff985f,0x3ffa0bfd,0x0ffef802,0x0bfff500,
    0xe800bfee,0x803ffa80,0x304fb85b,0x03fe23ff,0x42fe4698,0xfdb01ff9,
    0x00f801df,0x7c007ff1,0xf303fc81,0xdfb0288f,0x0bfe0620,0x3ee02ffc,
    0xd005d84f,0x07ffa0bf,0x7fdc17fa,0x4ffbe804,0x09ff7b00,0x37001bfa,
    0x3a01bfa0,0x3e04fd82,0x809ff13f,0x7d427cc5,0x3ff2f607,0xf8807c05,
    0x207e003f,0x0ff302fd,0x20037ec0,0x0ff902ff,0x75c3ffd0,0x20bfd000,
    0x5fe83ffc,0xd00dff30,0x9801ffb3,0xf884ff8f,0x8044005f,0x1aa02ffb,
    0x9fd02ff4,0x03027ff4,0x7b02fe40,0x0f80fff6,0x4007ff10,0x301ff81f,
    0x37ec00ff,0x5c0bfe00,0x6ff8807f,0x7f4003f3,0xd05ffb05,0x0ffea0bf,
    0x0ffe67a0,0x213fe9b0,0x00003ffa,0x3d817fe2,0x7f40bfb0,0x0bbffea5,
    0x00ff8800,0x17ff44f6,0x7ff100f8,0x7fc0fc00,0x400ff302,0x7fc006fd,
    0x200df502,0x002fcffb,0x7fc42ff4,0xd05fe81f,0x23d001ff,0x47e206fe,
    0x2ffc84ff,0x7fe40000,0xf900f880,0x717fe01f,0x003bffff,0x3d805f70,
    0x3e07ffe6,0x007ff100,0x81ff40fc,0x3f6007f9,0x817fc006,0x3f6005fb,
    0x5fe8004f,0xfd04ffb8,0x02ffd88b,0x0bfea3d0,0xd09ff2e4,0x800003ff,
    0x05b84ff9,0x7fc13fe6,0xffffe984,0x013a000c,0x1dff50f6,0x7ff100f8,
    0x7ec0fc00,0x400ff307,0x7fc006fd,0x4005f902,0xe8006ff8,0xffea9aef,
    0x333bfa04,0x2001cffe,0x221bfa1e,0x3a13fe1f,0x800001ff,0x017c0ffd,
    0x2a277ff2,0x3ee02ffe,0xa801efff,0xf707b005,0xf100f8bf,0x40fc007f,
    0x3621dffa,0x1bf6007f,0x3e07ff00,0x7ffd4006,0x5f7f4004,0x7401bccc,
    0x05ffbaef,0x3fee1e80,0x13fe35c2,0x0000bff6,0x6a8ffea0,0x7ffff700,
    0xc8801ff9,0x6c00efff,0x3607b000,0x4403e4ff,0x07e003ff,0x6e77ffec,
    0x3f6007fa,0x07ffc006,0x44003f91,0x001ffe9f,0x740017fa,0x00ffee5f,
    0x45ff83d0,0x6427fc2f,0x000004ff,0x001ecdfd,0x005ff822,0x9013ffa6,
    0xfd01ec00,0x7c403e5f,0x803e003f,0xf98dfffc,0x01bf6007,0xf9bd9ff0,
    0x9f44003d,0x3a006ff8,0xbfd0005f,0x2001ffd8,0xa8ffdc1e,0xfa84ff86,
    0x7000005f,0x001f15ff,0x120ffdc0,0x440dff30,0x880f6003,0x200f9fff,
    0x0f1004ff,0x3fcc1510,0x800dfb00,0x00a98aff,0x7fdc5d80,0x00bfd004,
    0xff117fa0,0x220f400d,0xff07d5ff,0x003ffa09,0xbff10030,0xfe8000b9,
    0x7fc80683,0x3d800220,0x07fffcc0,0x2600bfd0,0x0ff30006,0x20037ec0,
    0x5c0002ff,0x003ffd06,0x3a000bfd,0x04ff985f,0x7ff903d0,0x5413fe0f,
    0x032006ff,0x00fffe40,0x3e0bf700,0x0037dc01,0xf7007b00,0x7fe401ff,
    0x0005c800,0x7ec00ff3,0x017fc006,0x2601f500,0x7f400eff,0x0bfd0005,
    0x3a00bff2,0x04fff881,0x7fdc0bff,0x2002c805,0x20006ff9,0x037e05fc,
    0x0ee03fe8,0xf9004e80,0x1ff4401f,0x40003ee0,0x3fa007fa,0x017fc007,
    0x6402f980,0x37fc05ff,0x206ff800,0x17c02ffe,0xff00ffd8,0xbdffa80d,
    0x000b6a21,0x64000ff6,0x0f7fc04f,0xfa817f22,0x00bf002f,0x3e6007ec,
    0x0fe4c0cf,0x01ff7000,0x001fff10,0x2000ffe2,0x7cc00ffb,0xfff304ff,
    0x1fff1000,0x40bffe20,0x09f304f9,0x2601ffe6,0xbdefffed,0x01f50001,
    0x073b2a20,0x37ff6fa0,0x7cc03ffe,0x3ff2601f,0x0e8804ef,0xeeffd980,
    0x30001dff,0x209dfff9,0xcfffffc9,0x3fffb201,0xffeb801c,0xffd903ef,
    0x3f6a9fff,0x401cffff,0xcfffffda,0x4ffffa81,0x07bfffb5,0xfffda83b,
    0xa8800cef,0x00a00001,0x0c001a98,0x88006aa6,0x44000000,0x2aa62000,
    0x00000009,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x33260000,0x004ccccc,0x99999995,0x666665c3,0xcccccb84,0xccca80cc,
    0x999953cc,0x66443999,0x542ccccc,0xcccccccc,0x32a3cccc,0xcccccccc,
    0x9930cccc,0x99999999,0xcca87999,0xaabccccc,0xf980000a,0xccccca83,
    0x001aaccc,0x20003a80,0x9803dedb,0xd880c01d,0x2e217544,0x4001cfff,
    0x502fffb8,0x7d405dff,0x7cc03fff,0x7fdc41ef,0x3ffea02f,0xcdefd80c,
    0xfffccccc,0x577fdc42,0x1ffdcaaa,0x2abbfea2,0x86fccaaa,0xccefffc8,
    0x003effed,0x6440ffa0,0xdcabceff,0x3a0002ff,0xffe88006,0xea80efff,
    0x40ea01ff,0x17fa1ffc,0x20003ffc,0x17ea06ff,0x00fffcc0,0xdff00774,
    0x201ffb00,0x27fd403d,0x7cc0bff0,0x4c06ff82,0x20bff107,0x000effd8,
    0xf101ffe4,0x3bfa60bf,0x0ffcc000,0x2e73ba00,0x65546fff,0x07d101ff,
    0x0bfb1be6,0xd0001bfa,0x013e60bf,0x9809ff70,0x02ff401f,0x80b03fe4,
    0x3e00eff8,0x7415c05f,0x3a05806f,0x77fd405f,0x7fbd5000,0x2205fe80,
    0x7ec004ff,0x41aa005f,0xff882ffd,0x8007fb01,0x0dfb04fc,0x885fe800,
    0xffd0004e,0x7401ec03,0x07fc805f,0x03ffb012,0x0c405fe8,0x014037ec,
    0xff900bfd,0xfb3f100b,0x405fe807,0x3e2006fd,0x39000ffd,0x7c13fe60,
    0x77ff441f,0x2fb801cc,0x8000dfb0,0x027445fe,0x20dff300,0x0bfd006a,
    0x2000ff90,0xfe804ffb,0x0dfb0005,0x805fe800,0x6c01fff8,0xfe807fb3,
    0x007fe405,0x03ff9db8,0x04fe8030,0xfea983ff,0xf9800aad,0x000dfb01,
    0x13e65fe8,0x0ffee000,0x3fa003f1,0x007fc805,0xd006ff98,0xfb00e0bf,
    0x3a00cc0d,0x9ff7005f,0x07fb2dc0,0x7f405fe8,0x7f4be006,0x5fb00006,
    0x7ec07fe0,0xb03c4003,0xfe8000df,0x00009f35,0x09b0fff4,0x6402ff40,
    0xffe8007f,0x20bfd001,0x9037ec06,0x005fe805,0x3e20dff5,0xfd00ff60,
    0x027fd40b,0x0bfea6a8,0x403fa000,0x07fb01ff,0x37ec0d00,0x277fa000,
    0x4c00004f,0x001f56ff,0x7e402ff4,0x1ffe4007,0x333bfd00,0xefd80fb5,
    0x2fba9999,0x8802ff40,0xd85d07ff,0x077f403f,0x007ff953,0x017fe1f4,
    0x7c07f100,0x007fb01f,0x006fd800,0x7fff7f40,0x7dc00001,0x74002ebf,
    0xffffffff,0x2007ffff,0x74005ff9,0x7ffeeeff,0x7777fec0,0x7402ffee,
    0x3ffe005f,0x1fec2dc0,0x3fffffa0,0x2002ffff,0x07fe40f9,0xf80d9000,
    0x007fb01f,0x006fd800,0x7fdeff40,0x7400001f,0xfe8005ff,0x007fc805,
    0x8001ffd1,0x407985fe,0x05d106fd,0xf1005fe8,0xd80e98ff,0x22ff403f,
    0x01dffca8,0x4ff884c8,0x801f1000,0x07fb01ff,0x032e0b26,0xd0001bf6,
    0x07ffeebf,0x2ffa8000,0x805fe800,0xffb007fc,0x0bfd0005,0x40dfb012,
    0x02ff402a,0x0f46ff98,0x7f403fd8,0x07ffea05,0x9999af88,0xb0007fe9,
    0x203ff007,0x7ffd03fd,0x7ec3ffd4,0x2ff40006,0x0003fff7,0x000bfe60,
    0x3f2017fa,0x05ffa807,0x060bfd00,0x0c40dfb0,0x54017fa0,0x3bbee5ff,
    0xeeffeeee,0xb80bfd06,0x3bee06ff,0xffeeeeee,0x802e4002,0x07fb01ff,
    0xff997ffa,0x0037ec2f,0xff717fa0,0xf300003f,0xbfd0005f,0x880ff900,
    0xd0000eff,0x3f6000bf,0x2ff40006,0x322ffd80,0xffffffff,0xbfd07fff,
    0x207ff980,0x037f402e,0x7fc00b70,0x2207fb01,0x164cc69a,0x14c01bf6,
    0x7fdc2ff4,0x7cc0001f,0x5fe8002f,0x6c07fc80,0x81a801ff,0xfb0005fe,
    0x3a06600d,0x5ff9805f,0x4cccccc4,0xd019cfd9,0x7ff980bf,0xff700d50,
    0x800d5003,0x4bf901ff,0x81d03b81,0x20d006fd,0xfff705fe,0x7fcc0003,
    0x05fe8002,0x3ee07fc8,0xd01b004f,0x3f6000bf,0xfd01d006,0x01ffd00b,
    0x7403fd80,0x27fe405f,0xff8803e8,0x50075405,0x3ee03ff0,0x80e80cbf,
    0x807fe84a,0x40dff05c,0x0003fffb,0xf0007ff5,0x0ffb00df,0x5401bfe6,
    0x000bff06,0x16e01bfa,0xfd102ffc,0x7fb0003d,0x2205ff80,0x0fa81fff,
    0x205ffb00,0x3d9980ea,0xfd00ffc4,0xb80c985d,0x9afff883,0x2fdaa999,
    0x7c07ff88,0x4000cfff,0x44004ffc,0xfff807ff,0x99affe81,0xfda99999,
    0x007ff985,0x881fff88,0xff882fc9,0xff75109e,0x1fec0009,0x413dff10,
    0x881effb9,0x3ff2007f,0xfffffa86,0x440fffff,0x280402ff,0xffc98130,
    0xffffffff,0x3f6a0fff,0x261cefff,0xdffffffd,0x7fff6401,0x7ed404ef,
    0x221cefff,0x2cfffffc,0xfffffff7,0x7fffffff,0x77fffed4,0x7f64c01c,
    0xffffffff,0x7fed47ff,0xcdefffff,0x7ec0001a,0xffffda83,0x3defffff,
    0x09dfff70,0x7ffffecc,0xffffff34,0x64cbffff,0x002cfffe,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00d40000,0x00000000,0x4c399990,0x665c3ccc,0x999971cc,
    0x22666419,0x204bcec9,0x001cddb9,0x4015bd93,0x5c0cdeca,0x260ccccc,
    0xdb883ccc,0x96cc02ce,0x23d984da,0x764c2deb,0x44b6a00c,0x99501ddb,
    0x99999999,0x4333332a,0x7641cccb,0x6c003b20,0x000cb802,0x0ecc0000,
    0xfe985ff5,0x21ffec46,0x7440dffb,0x2a23361e,0x265f707e,0x5fe404fd,
    0x6c41ffa8,0x21ffc9ad,0x880effb8,0x997dc0cf,0xffea83fe,0xd52fffab,
    0xffdd39ff,0x3ffbee5f,0x9bffea86,0xb80fffee,0xfcaaabcf,0x8bffea4f,
    0x7fc41ef8,0x2007ff13,0xdfc8802d,0x54000001,0x82ff83ee,0x2ff886fb,
    0x43d03fe8,0x543d40f8,0x904fe81f,0x645fd81f,0xfd86fd85,0xf881f105,
    0xfd03fd46,0xe81b919b,0xdfb10cdf,0x81ffcc79,0xfd10ddff,0x3fa05909,
    0x2a4ff986,0x13ff880f,0x0b6007ff,0x02efb880,0x3bee2000,0x2a0bfa02,
    0x50bf906f,0xfb8d30df,0x837c4681,0x1fcc1ffa,0x05f33fd4,0xff985ff5,
    0x5fa83b80,0xfd807fcc,0xa85fd806,0x04fd82ff,0x0bf90bfb,0x403ff209,
    0x01e89ffb,0x02ff87fe,0x2a0005b0,0x30000bfe,0xfd0039f9,0x260df505,
    0x0ffcc0ff,0x85ff50f2,0xff02fdc1,0x1102fc8b,0x666667e4,0x3fe83ffd,
    0x881700e8,0x07fb01ff,0xff109fb0,0x360bf901,0x006fa83f,0xfd805ff5,
    0x07ec03de,0x0b6003fb,0x39fb3000,0x02ff6a00,0xfa82fe80,0xdb0ffa06,
    0x7c40e8bf,0x7fb01dff,0x3fa37ec0,0x333fb001,0x70133333,0x5005a8ff,
    0x3603ffbb,0x04fc803f,0x0bf701ff,0x1fe60ff6,0x2013fe60,0x7c806ff8,
    0x05b003e4,0x37f22000,0x02eeb882,0xf505fd00,0xd337dc0d,0x416a1ff3,
    0x40dfffd8,0x1ff204ff,0x3fa005ff,0x2ff88000,0x19d50076,0x1fec07fe,
    0xff827e40,0xfb05fb80,0xd00ff307,0x7fdc00df,0x1aa2d401,0xfdddddd5,
    0x3ddddddd,0x1df71000,0x00007fea,0x0df505fd,0xd2c8ffc4,0xf500b67f,
    0x37fc1dff,0x5ff8bf70,0x0003fd00,0x203457f2,0x80ffc2fb,0x4fc803fd,
    0xbf701ff0,0x3e60ff60,0x007fe407,0x980dfdd0,0x266224c4,0x99bd9999,
    0x88001999,0x7f5c2efb,0x5fd0000b,0xfd80df50,0x23bee68c,0xffc88106,
    0x6403ffa3,0x103fec4f,0x28817f65,0x0773ff30,0x0ffc27dc,0xfc803fd8,
    0xf701ff04,0x260ff60b,0x0bfea07f,0x4ff8bd80,0x16c00000,0x6fe4c000,
    0x067ed401,0x2a13f600,0x67fcc06f,0x40f7fe23,0x2e6fc81c,0x85fb02ff,
    0x21b02ffc,0x01902ffb,0xd00767ec,0x203ff05f,0x4fc803fd,0xbf701ff0,
    0x3e60ff60,0x209ff107,0x3fea5a82,0x36000001,0x3f6a0002,0x7e4c000c,
    0x8df9001d,0xfe807fe9,0x900ffc87,0xff8bf30b,0xff10bf04,0xf1264c5f,
    0x12e217ff,0xe809ff50,0x08ffd45f,0x7ec027ec,0xb81ff884,0x309fb05f,
    0x817fa0ff,0x3f6074c4,0x55554c0e,0x016c002a,0x00bbae20,0x0bbee200,
    0xb959ff50,0x5c079ff7,0x205f984f,0x20fdc2fc,0x1b623ff9,0xfeffffb8,
    0x7fffd40e,0xfe800fff,0x5e7fdc01,0x40ddffbd,0x5fe806fe,0xfc82ff98,
    0xf509ff07,0x80ffc81f,0x20fa24c8,0x7ff45ff9,0x2000ffff,0xbf91002d,
    0x2a000003,0xff900cfe,0x02fbea9f,0x05d00f88,0x6edf7f64,0xdbdfd102,
    0xfffa8019,0xfff300be,0x1ae003df,0x47bff220,0x3f6a0efc,0xfda82dff,
    0xffd92cff,0xfffb319d,0x3fffaa5b,0xefffc8ac,0xffffff53,0x3ea9ffff,
    0x3ff622ef,0xbbbb92ef,0x16c001bb,0x00067d40,0x1fd98000,0x00c41510,
    0x8200c030,0x331000a9,0x40033000,0x0c4000a8,0x00101100,0x00000000,
    0x00000000,0xd8000000,0x00008802,0x00110000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x30000000,
    0x801b0003,0x88888888,0x22088888,0x002205fe,0x22222204,0x88888888,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x07f80000,
    0xf7027dc0,0xffffffff,0x443fffff,0x7fe440ff,0xf89200be,0xffffffff,
    0x001fffff,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0xf1003fc0,0x444403f3,0x88888888,0x42f98088,0xdfeb88bc,0x222224c2,
    0x88888888,0x00000088,0x00000000,0x00000000,0x00000000,0x00000000,
    0xed800000,0x817a6bb1,0x0000d74c,0x20912a00,0x0eedffc9,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0xb0000000,0xff3975ff,
    0x2e83e60b,0x47000000,0x01ba8008,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x98000000,0x01cfddfc,0x981f30ba,0xcccccccc,
    0x00cccccc,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x3ae20000,0x41ae00bf,0x5dddcc4c,0xbbbbbbbb,0x000000bb,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x80000000,
    0xfdbadfea,0x880fc41d,0x0000001f,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x657fa000,0x04c8dfb4,0x000002dc,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x74530000,0x00d886a6,0x000001d8,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x0ff00000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x99000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,
};

static signed short stb__times_31_usascii_x[95]={ 0,3,1,0,1,0,1,1,1,0,1,0,1,1,
1,0,1,3,0,1,0,1,1,1,1,1,2,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,
0,0,-1,0,0,0,0,1,0,0,0,0,0,0,0,2,0,1,0,-1,1,0,-1,0,0,1,1,0,0,0,
-3,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,0,0,3,2,2,0, };
static signed short stb__times_31_usascii_y[95]={ 24,5,5,5,3,5,5,5,4,4,4,7,21,16,
21,4,5,5,5,5,5,5,5,5,5,5,11,11,7,11,7,5,4,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,5,5,28,5,11,4,11,4,11,4,11,4,4,
4,4,4,11,11,11,11,11,11,11,7,11,11,11,11,11,11,4,4,4,14, };
static unsigned short stb__times_31_usascii_w[95]={ 0,4,9,14,12,23,20,3,8,9,12,16,5,8,
5,8,12,8,13,11,14,12,12,12,12,12,4,6,16,16,16,11,25,20,18,17,20,17,15,20,20,9,11,21,
17,25,21,20,15,20,19,14,17,20,20,27,20,20,17,7,8,7,13,16,6,13,15,12,15,11,12,14,14,8,
9,15,8,22,14,14,15,14,10,9,8,14,14,20,14,14,12,9,2,9,16, };
static unsigned short stb__times_31_usascii_h[95]={ 0,20,9,20,24,20,20,9,26,26,12,16,8,3,
4,21,20,19,19,20,19,20,20,20,20,20,14,18,15,7,15,20,27,19,19,20,19,19,19,20,19,19,20,19,
19,19,20,20,19,25,19,20,19,20,20,20,19,19,19,25,21,25,10,3,5,14,21,14,21,14,20,20,20,20,
27,20,20,13,13,14,19,19,13,14,18,14,14,14,13,20,13,27,27,27,5, };
static unsigned short stb__times_31_usascii_s[95]={ 255,245,244,69,116,97,149,250,60,69,52,
1,250,244,250,138,170,225,211,183,156,195,208,221,84,40,250,243,35,79,18,
68,11,190,171,1,135,117,101,215,62,246,234,19,1,229,80,194,193,95,209,
53,138,102,19,121,172,41,83,79,129,87,65,120,96,153,163,113,147,126,56,
41,26,17,1,1,236,178,201,98,156,123,167,88,234,52,138,67,229,179,216,
50,47,37,103, };
static unsigned short stb__times_31_usascii_t[95]={ 1,1,91,29,1,29,29,71,1,1,106,
91,81,101,16,1,29,71,71,29,71,29,29,29,29,50,1,71,91,106,91,
50,1,71,71,50,71,71,71,1,71,29,29,71,71,50,50,1,50,1,50,
50,50,50,50,29,50,71,71,1,1,1,106,106,106,91,1,91,1,91,29,
29,29,29,1,29,1,91,91,91,50,50,91,91,71,91,91,91,91,1,91,
1,1,1,106, };
static unsigned short stb__times_31_usascii_a[95]={ 112,149,183,224,224,373,348,81,
149,149,224,253,112,149,112,124,224,224,224,224,224,224,224,224,
224,224,124,124,253,253,253,199,412,323,299,299,323,274,249,323,
323,149,174,323,274,398,323,323,249,323,299,249,274,323,323,423,
323,323,274,149,124,149,210,224,149,199,224,199,224,199,149,224,
224,124,124,224,124,348,224,224,224,224,149,174,124,224,224,323,
224,224,199,215,90,215,242, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_times_31_usascii_BITMAP_HEIGHT or STB_FONT_times_31_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_times_31_usascii(stb_fontchar font[STB_FONT_times_31_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_times_31_usascii_BITMAP_HEIGHT][STB_FONT_times_31_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__times_31_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_times_31_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_times_31_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_times_31_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_times_31_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_times_31_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__times_31_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__times_31_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__times_31_usascii_s[i] + stb__times_31_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__times_31_usascii_t[i] + stb__times_31_usascii_h[i]) * recip_height;
            font[i].x0 = stb__times_31_usascii_x[i];
            font[i].y0 = stb__times_31_usascii_y[i];
            font[i].x1 = stb__times_31_usascii_x[i] + stb__times_31_usascii_w[i];
            font[i].y1 = stb__times_31_usascii_y[i] + stb__times_31_usascii_h[i];
            font[i].advance_int = (stb__times_31_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__times_31_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__times_31_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__times_31_usascii_s[i] + stb__times_31_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__times_31_usascii_t[i] + stb__times_31_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__times_31_usascii_x[i] - 0.5f;
            font[i].y0f = stb__times_31_usascii_y[i] - 0.5f;
            font[i].x1f = stb__times_31_usascii_x[i] + stb__times_31_usascii_w[i] + 0.5f;
            font[i].y1f = stb__times_31_usascii_y[i] + stb__times_31_usascii_h[i] + 0.5f;
            font[i].advance = stb__times_31_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_times_31_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_times_31_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_times_31_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_times_31_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_times_31_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_times_31_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_times_31_usascii_LINE_SPACING
#endif

