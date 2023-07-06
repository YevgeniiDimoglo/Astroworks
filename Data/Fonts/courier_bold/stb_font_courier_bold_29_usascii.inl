// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_courier_bold_29_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_courier_bold_29_usascii'.
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

#define STB_FONT_courier_bold_29_usascii_BITMAP_WIDTH         256
#define STB_FONT_courier_bold_29_usascii_BITMAP_HEIGHT         94
#define STB_FONT_courier_bold_29_usascii_BITMAP_HEIGHT_POW2   128

#define STB_FONT_courier_bold_29_usascii_FIRST_CHAR            32
#define STB_FONT_courier_bold_29_usascii_NUM_CHARS             95

#define STB_FONT_courier_bold_29_usascii_LINE_SPACING          14

static unsigned int stb__courier_bold_29_usascii_pixels[]={
    0x00206620,0x33101002,0x4c400033,0x16c40099,0x8a200000,0x44550028,
    0x2ae6200b,0x35751000,0x80aaa880,0x55441aa9,0x0379951a,0x00af2a60,
    0x33333333,0x26200000,0x06e200ab,0x51bcca88,0x7fec0355,0x540bfee1,
    0x25fc885f,0x007ffffb,0x7ffe4dd1,0x81bee06f,0xf10002fb,0x1013fa5f,
    0x417f21ff,0x03fffff9,0x77ffffe4,0xfffff980,0x57ffff60,0xffdffff8,
    0x300dffff,0x3dfffffd,0x3fffffe0,0xdd501fff,0xfff30017,0xfff109ff,
    0xfffff503,0x09ffffbf,0xffc87ff6,0xe87fb82f,0x3fff26ff,0x1ff9007f,
    0x81fffff2,0xffb01ffd,0x47ff6000,0x3e601ffd,0xf30bfd1f,0x05ff97bf,
    0xffffffd1,0xfff985ff,0x3fff20ff,0x3ffffa4f,0xffffffff,0x7ffffc40,
    0xff80ffff,0x2fffffff,0x05fddfd8,0x7fffffcc,0x27ffd42f,0x3fffffee,
    0x03ffffff,0xffa81555,0x7cc7fc85,0x7ed4c0cf,0x25ff8807,0xa80aaffc,
    0x2ffffffe,0x3000bfea,0x2ffccdff,0x3fa3ff50,0x7cc4fd84,0x89dffd85,
    0x440fffb9,0x7ff706ff,0x45ffff30,0x7d46ffc9,0xbff732df,0x5555bff0,
    0x547f1035,0x33ffa01f,0x2a1ffea8,0x3fe64fff,0x3fff262f,0x3f60000d,
    0x7e47fc86,0x403fe407,0x1ff22ffb,0xffffffb8,0x037f44ff,0xfd0bff20,
    0x43fea03f,0x837cc4ff,0x827fdc7e,0xffb86ff9,0x3e06ff82,0x3ff901ff,
    0x0ffb01b8,0x7dc007ff,0xff981fc0,0xf31ffcc4,0x07fec7ff,0x54c4ffc8,
    0x42aaaaaa,0x47fc86fc,0x3fe407fc,0x3f237f40,0x26fbfa07,0x7dc4ffc9,
    0xdff1002f,0x2e09ff50,0xb87ff0ff,0x7c1fb04f,0x0ffdc06f,0xff71bfe2,
    0x102ffc05,0x7ec007ff,0x2003ff87,0x407ea2f9,0x5ff81ffc,0xff8bffe6,
    0xb93fe205,0xffffffff,0x7e437e45,0x3203fe47,0x17fd407f,0x7fcc1ff2,
    0xff82fb82,0x05ff7006,0xeb883ffa,0xaeffccff,0x7ecc5f90,0x05ff10ff,
    0xff707ff0,0x3e037fc5,0x13fe204f,0x7c2ffdc0,0x03dfedef,0x31bf33f6,
    0x7fc83fec,0xff87ffe2,0xb93fe204,0xffffffff,0x7e437e45,0x3203fe47,
    0x437f407f,0x9ff107fc,0x0ffdc001,0xc807fec0,0x3fffa1ff,0x4fffffff,
    0x3ffe63fb,0x03ff50ff,0x3fe09fd0,0xf805ff76,0x5ff901ff,0x7ffffec0,
    0xffffff80,0xfb880dff,0x2fec98cf,0x3fea0bfd,0xfd87ffe1,0x89ff900f,
    0xfe999998,0x7e437e45,0x3203fe47,0x0ffea07f,0xffd81ff2,0x7c401bdf,
    0x07fe805f,0xffb8bfee,0xefffffff,0x2ff21fb2,0x1ff70fd8,0x2e0dfb00,
    0x806ffaff,0x930befff,0x3e601fff,0xff04ffff,0x9fffbbff,0xdfffca80,
    0x7cc13fa2,0xb83ffa1f,0xf930beff,0x3f6009ff,0x90e7fdc5,0x1bfee2ff,
    0x7f40ff90,0x440ff907,0x2dfffffd,0xf007ff20,0x27fcc0df,0x1ffaafec,
    0xb37c47ec,0x007fea1f,0xfff817fa,0xfff802ff,0xffffefff,0x7ff6dc01,
    0x441c982f,0x7e540ffe,0xfe80adff,0x743ff304,0xffffc87f,0x04fffffe,
    0xff88bfb0,0x7e5ff26f,0x3fe402ff,0xf903ff98,0xffd9100f,0x3fe207ff,
    0x817fe204,0x5fe85ff8,0x8fd81ff5,0x4c3f66f8,0x7fc403ff,0x1bffee03,
    0x7fff7fc0,0x4001efff,0x2000fffa,0x3ffa2ffa,0xe82db9ad,0x43ff505f,
    0xfff907fd,0x09ffdfff,0xff517f60,0xfabfe49f,0x3fe404ff,0xf900ffd8,
    0xfeb8800f,0x403ff607,0x3e605ff8,0x4effcc4f,0x87ec1ffb,0x20fd9cfc,
    0x3f200ffe,0x17ffc01f,0xcb8bff80,0x2a0002cd,0x3e2002ff,0xffa8aa3f,
    0x83fe46fe,0x17ee0ffc,0xf1cdcb88,0x17f6009f,0x7fc83ff9,0xf901bf62,
    0x409ff30f,0x03d507fc,0x7cc07fea,0x81bfe04f,0xfff33ffa,0xdfffffff,
    0xffe88fe4,0x17fee4ff,0x2202ffd4,0x3fe006ff,0xf8800003,0x3fe6003f,
    0x7cc37a03,0x3e0bfea2,0x2000187f,0xbfb004ff,0x7fc86fc8,0x3f203fe4,
    0x200ffc87,0x0bfd07fc,0xffb01ff2,0xb81ffa01,0xffff32ff,0x1fffffff,
    0x99930bea,0x9beffc83,0x400fffda,0x3e002ffb,0xb800003f,0xc80261ff,
    0x85f301ff,0x317fe25e,0x800009ff,0xbfb004ff,0x7fc86fc8,0x3f203fe4,
    0x202ffc47,0xdfff07fc,0x09ffb735,0xf903ff98,0x83ff603f,0xfeacffb9,
    0x013e60af,0x3ffffee0,0x33301eff,0x26001fff,0x20009cff,0xcba99bfe,
    0x33fe27ff,0x6ffca99a,0x89f0fe20,0xffcadffd,0x8800080f,0xd800dff9,
    0x6437e45f,0x203fe47f,0x0ffe47fc,0x7f41ff20,0xffffffff,0x507fe801,
    0xdff109ff,0x3f65ff30,0x0001ff06,0x19fffff5,0xffffff30,0xffe803ff,
    0x8803ffff,0xffffffff,0x7fff42ff,0x01ffffff,0x07ed5fe4,0x7ffffff4,
    0x2006fc82,0x3ffffffe,0x3f22fec0,0x7e47fc86,0xf13fe407,0x0ff900bf,
    0x3ffff7ee,0xff5000bf,0x703ffa07,0x3ff307ff,0x77d417f6,0xfc813222,
    0x46e21dff,0xfffffff9,0x3ffe202f,0x5004ffff,0xbffffffd,0xffff9101,
    0x91001bff,0x3a207dff,0xfb02ffff,0x7fffc00f,0x7f404fff,0x7e437ec5,
    0x3203fe47,0x007fee7f,0x7ec01ff2,0x6fe8000f,0x7c49ff70,0x1ffa80ff,
    0x7fe40bfd,0xf705ffee,0xfdffffff,0x555544bf,0xaa8800aa,0x88001aaa,
    0x310009a9,0x22000355,0x00151001,0x55440013,0x7c401aaa,0x07ff913f,
    0xdffa8ff9,0x9ffb2e21,0xff9006ff,0x3fe40379,0x82ffa800,0xff70fff8,
    0x7c3fea09,0x7fedc04f,0x3fffe03d,0x2fffffff,0x00000000,0x00000000,
    0x00000000,0x99988000,0xffb1ffeb,0xd0ff701f,0x7ffecfff,0x005ff77f,
    0x03fffff2,0xf0003fe4,0x4bfea0df,0xff300efe,0x000017f4,0x2a26af2a,
    0x2ee60adc,0x3bbbbbbb,0x77777754,0xeeeeeeee,0x000000ce,0x00000000,
    0x2e000000,0x4fffffff,0x7cc033aa,0x2a4fc884,0xdfb7fffe,0x7fffe400,
    0x0013e605,0xd900ffb8,0x13007ae1,0x00000144,0xffffc800,0x747fffff,
    0xffffffff,0xffffffff,0x00000002,0x00000000,0x3ff20000,0x0003efff,
    0x1ea80000,0x00400000,0x0002ec00,0x00000000,0x3bbb2000,0x46eeeeee,
    0xccccccc9,0xcccccccc,0x00000003,0x00000000,0xaa980000,0x0000000a,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x4c017730,0xaa98bccb,0x0099980a,
    0x99999980,0x80019999,0x2a200998,0x573001bc,0x00199880,0x4004c400,
    0x98800998,0x33300009,0x004c0033,0x02aea200,0x01aca880,0x80099980,
    0xfc880039,0xfc83ffff,0xffefffff,0x1ffffc7f,0x3fffe200,0x07ffffff,
    0x827fff40,0x0efffffc,0xbffffd10,0x07fffa81,0xfffd9800,0xff700dff,
    0x4fffe809,0x7fffc400,0x0df3007f,0x7fffe400,0x3f6200ef,0x000dffff,
    0x7107fff5,0x8800fffb,0x4ffffffe,0x7fffffec,0x226fffff,0x4003ffff,
    0xfffffff8,0x7c007fff,0xffc84fff,0x40ffffff,0xfffffff8,0x03fffdc5,
    0x7ffff400,0xff703fff,0x4ffff809,0x7fffc400,0x0ff7007f,0xffffd100,
    0xd105ffff,0xdfffffff,0x0ffffa00,0x0ffffff7,0x56fff440,0x3effa830,
    0x03fffd71,0x0007ff51,0x555559ff,0xa8800ffd,0x77fcc4ff,0xb89ff932,
    0xffd98cff,0x003fecc2,0x2af3fea0,0x55100dcc,0x4ffa8803,0xfdaa8800,
    0x00ff7007,0x313bffb0,0xfc83fff7,0x9ffb52df,0x3ffffb80,0x3fffffec,
    0x04ffe880,0xf980ffe8,0x0ffe207f,0x22036e00,0xff0004ff,0xe81ffb89,
    0x742ff46f,0x03fdc0ff,0x0017f600,0x027fc000,0x101ff200,0x5555ffb5,
    0x13fee015,0x3fe37fcc,0x440dff05,0x443fffff,0x200ff91a,0xff003ffb,
    0x103ff40b,0x2f32a7ff,0x5ff50001,0x8de65440,0x83fe44ff,0x0ffe27fd,
    0xff707fee,0x3006f32a,0x5555bff5,0x2aaaa201,0x4c9ff002,0xfc800aaa,
    0x7ffffc07,0x81ffffff,0x7fdc06ff,0x7e403b22,0x3efff607,0x03fe403f,
    0x40227fe8,0x3f203ff8,0x3f7fe207,0x00dfffff,0xf703fec0,0xffbfffff,
    0x443ffa89,0x0bfe65ff,0xff70ffe6,0x07ffffff,0x3ffffff2,0x7cc0ffff,
    0xf007ffff,0x3fffee9f,0x03fe402f,0x3ffffffa,0x7c41ffff,0x03ff802f,
    0x260bff10,0x03ff8dff,0x7c403fe4,0x1efffbcf,0x3fe06ff8,0x3fffe207,
    0x0fffffff,0x209ff100,0xfffffffc,0xffe84fff,0x42fffdbe,0x4ffe85ff,
    0x7fffffdc,0xffc83fff,0xffffffff,0x7ffffc40,0x329ff007,0x402fffff,
    0xfc8807fc,0x3019999f,0xbfd003ff,0x40fff600,0x3ff88ffe,0x4c03fe40,
    0xffffffff,0x417fec2f,0x3e207ffb,0xfb51cfff,0x3fea00bf,0x0bfff982,
    0x109fffd5,0x9fffffff,0x3225ffb0,0x7fdc5fff,0x417fa63f,0x999dfe98,
    0x3feccc01,0xffacff80,0xff9001df,0x801fee00,0xfd800ffb,0x2ffec406,
    0xff14ffb8,0x807fc807,0xdbeffff9,0x3fe60fff,0xfffeaadf,0x0bffe207,
    0x6c00ffec,0x03ffd07f,0x3ee13ffa,0x86ffffff,0xfffefff9,0x0ffdc6ff,
    0x3fa03fe4,0x0ff90004,0x3fffbfe0,0x03fe4004,0x26007fb8,0x5fe801ff,
    0x417ffa20,0x3fe26ff8,0x403fe403,0x7d45fff8,0x7fffdc3f,0x207fffff,
    0x3ea06ff8,0x27fc403f,0x3ee06ff8,0x67ffcc4f,0xa85ffeb9,0xffefffff,
    0xfb83fdc4,0x0027f407,0xff007fc8,0x90005fff,0x1fee00ff,0x403ff880,
    0xfd303ff8,0x5ffe40bf,0x403ff999,0xfff007fc,0xd30bff01,0xffbbffff,
    0x2027fc40,0x7fd404ff,0x203ff882,0x7fe44ff8,0x7107fe81,0x85ff759b,
    0x0ff707fb,0x90004fe8,0x3ffe00ff,0x64000eff,0x0ff7007f,0x200ffe80,
    0xffa81ffc,0x3ffe204f,0x5fffffff,0x6c01ff20,0x40dfd06f,0x0ff70a98,
    0xf3037fc4,0x07fd807f,0xffa817fe,0xfb837f44,0xfff8801f,0xfb83fdc0,
    0x0027f407,0xff007fc8,0x001dffbd,0xfb803fe4,0xfa81100f,0x0bff505f,
    0x8807fff7,0xffffffff,0x1ff206ff,0x2217fe40,0x7f4004ff,0x07ffe206,
    0xf100ffec,0x07ff409f,0x7e44ffe8,0x00ffc80f,0x5c1ffecc,0x80ff707f,
    0xf90004fe,0x653fe00f,0xf9001fff,0x33fe600f,0x86fedb9a,0xda9beffc,
    0x7fe40fff,0x5555002f,0x019ff755,0xe8803fe4,0xffeb9bef,0x36a66602,
    0xff9304ff,0xfd735bff,0x2ffa80bf,0x2b7ffea0,0xbefffec9,0x537dff50,
    0x9ba8dff9,0xa85fffeb,0x36a0bffe,0x32e60bff,0x1bccceff,0xffeccca8,
    0x2e60bccc,0x3fff24ff,0x3332a0bc,0x0bcccffe,0xffffffb0,0x3ff60dff,
    0x41efffff,0xcccefffc,0x5c403dcc,0x2e21dffc,0xcccffecc,0x3fffea01,
    0xff305fff,0x01dfffff,0xfffffff1,0x01ffffff,0xfc807fd8,0xffffffff,
    0x3ff64fff,0x21efffff,0xfffffff8,0xfffff985,0xbfffff35,0x7ffffffc,
    0x7fcc6fff,0xffffffff,0x93fffe4f,0x34fffffb,0xffffffff,0x3a609fff,
    0x02efffff,0x67ffffd4,0xfffffc80,0x407fffff,0x26fffffd,0xfffffffd,
    0x36a00fff,0x2a04ffff,0x0cffffff,0x3b7fff60,0x00cfffff,0xd5002fa8,
    0xff9fffff,0xfffc83df,0xffd80dff,0xfb101eff,0x3f627fff,0x3ff23fff,
    0x4fffffff,0x7ffffec4,0x322effff,0x3fa64fff,0xffb11eff,0xdfffffff,
    0x01aa9805,0x6401a880,0xffffffff,0x7f5407ff,0x3fae4fff,0x5fffffff,
    0x00135100,0x00035551,0x0001aa88,0x03531000,0x10035100,0x00000035,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x26666200,0x75300199,0x57100015,0x01333005,0x54401333,0x751001bb,
    0x26666035,0x99999999,0x19999981,0x804ccc00,0x99809998,0x30133100,
    0x02662013,0x00ccccc4,0x31033330,0x06662013,0x4c40ccc4,0x00999999,
    0x01333333,0x3fffff20,0xf702ffff,0xbfdfffff,0xffffec80,0x3fea5fcf,
    0xfff55fff,0xffda8bff,0x9102efff,0xdddfffff,0x7ffffffc,0x51ffffff,
    0xffffffff,0x3fe6019f,0x7fe46fff,0xfff34fff,0xffffc8df,0x1dffff33,
    0x21ffffe4,0xfffffffe,0x3fffea03,0xffffd2ff,0xfffffe89,0x3fffffa1,
    0xffffff92,0x7fccdfff,0xdfffffff,0x3ffff600,0xd83fffff,0xffffffff,
    0xfffb00ff,0x4fffffff,0x76fffffc,0x54ffffff,0xffffffff,0xffffe81f,
    0xff1fffff,0xffffffff,0x3fee3fff,0xffffffff,0xffffa81f,0x3fff60ff,
    0xffff35ff,0x7ffff41d,0x1fffff55,0x22fffff4,0xffffffff,0x3fffee04,
    0xfffff3ff,0x7ffffc4b,0x3ffffe2f,0xfffffb3f,0x2a1fffff,0xffffffff,
    0x55102fff,0x035bff75,0x3117bffb,0xfb01fff7,0xfd5115bf,0x67fd41ff,
    0x37fea60a,0x22b3fea0,0x7dc6ffb9,0xffb98adf,0xb55bff1f,0x3ff955ff,
    0x5557fecc,0x980fffeb,0x5440bffe,0x3660affe,0x7ffc43ff,0x13ffa60a,
    0x5105fff3,0x0055bff5,0x6c35ffb3,0x7cc0afff,0x5d441adf,0x2aaa24ff,
    0x40aaaffd,0xbaabffc9,0xf000fffe,0x17fea07f,0xffa87fb8,0x883ff605,
    0x0ffe02ff,0xff901ff3,0xfb837ec1,0x7e49ff1f,0xf707fe67,0x40bfee0f,
    0xff103ffa,0x83ffe20b,0xff103ffc,0x01fff43f,0x320027fc,0x3bff627f,
    0xa993fe00,0xc80bfe62,0x1ffa807f,0xf003ffa8,0x01ff607f,0x01ff2136,
    0x2ff88df3,0x0f20ffe0,0xdfb07fd4,0x4ff9fe20,0x1ff99ff2,0xff883fdc,
    0x5c1bfa03,0x3fea01ff,0x980bff35,0x4ffc8fff,0x8009ff00,0xdffd17fc,
    0x3a5fe801,0x03ff52ff,0x7d403fe4,0x00bfd01f,0x2ffc0ffe,0x00bfd000,
    0x02ff8815,0xe8800ffe,0x0effdc6f,0xff917f40,0x3ee07fc4,0x403ff907,
    0x6fe81ffb,0xfeaffd80,0xfffa800f,0x3fe005ff,0x4ffe4004,0xfb005fff,
    0x5d3ffe6d,0x1ff200ff,0x2607fea0,0x7ff004ff,0x0007ff10,0x4000ffe2,
    0x3fe02ff8,0xfffc8803,0x7ffff443,0x642981bd,0x7dc1547f,0xffecaaaf,
    0x22ffc406,0xf8803ff9,0x2002ffff,0x000efffc,0xf90013fe,0x400dffff,
    0xffff97fc,0xff901ff2,0x983ff500,0xf8012ffe,0x82ff883f,0x4c199998,
    0xf10002ff,0x01ffc05f,0x413fffee,0xffffffd8,0x03fe400e,0xffffffb8,
    0xfd800dff,0x003ff60f,0x002fffd4,0x0013ffe6,0xfc8009ff,0x005fffff,
    0xffff1ff7,0xc80dfb5f,0xeffa807f,0x55ffffee,0x41ffc09f,0x7fdc2ff8,
    0x3e27ffff,0xff10002f,0x201ffc05,0x8801effc,0x0effffda,0x5c01ff20,
    0xffffffff,0x27ff3000,0x6c004ff8,0x3a2000ff,0x2002ffff,0x819304ff,
    0xffebfffc,0xfbffa806,0x5fecffbf,0x5403fe40,0xffffffff,0xff81bf24,
    0xfb87ff03,0x20ffffff,0xf10004fe,0x01ffc05f,0x88001bea,0x3f202ffc,
    0x33ff7007,0x400bffd3,0x03ff76fe,0x4007fc80,0x1fffcffd,0x3609ff00,
    0x90ffe43f,0xff9807ff,0xfffd8ffe,0x03fe404f,0x67777fd4,0x883fe41b,
    0x0bfb02ff,0x83ff9551,0x3e0006fc,0x05ff105f,0x37c40150,0xfc817fa0,
    0x88ff7007,0xf7005ffd,0x000dff5f,0x7e400ff9,0x01dff35f,0x3fa09ff0,
    0x7f43fe45,0x3ffe200f,0x7ffff55f,0xa807fc80,0x7fc801ff,0x2e03ff70,
    0x3fea02ff,0x102ffd40,0x0ffd83fb,0x0000ffd8,0xf103ffa8,0x03fe40bf,
    0xffd07fb8,0x3fffe005,0x7fc8002f,0xb8dff500,0x4ff806ff,0x7fc8bfd0,
    0x7c04ff98,0x3ffe3fff,0x03fe402f,0x6400ffd4,0xfcaaceff,0x6fff406f,
    0xffeca99a,0xabeffd80,0x42fffba9,0xda9cfffa,0x013004ff,0x4defffd4,
    0x4c3fffda,0x2ccffecb,0x159ffd50,0x005fffc4,0x801ffff2,0xccffecb9,
    0x4fffb882,0x20efffcc,0xcceffcb9,0x2a5ffccc,0x7ec2cffe,0xfffd02cf,
    0x217ffec1,0xcffeccb8,0x7fed41cc,0xff702ccd,0x1dffffff,0xfffff980,
    0x00ffffff,0xfffffff9,0x3fee09ff,0x00efffff,0xf501ffe8,0xffffffff,
    0xfffff0bf,0xfb83ffff,0x543fffff,0x7cc05fff,0x3fa004ff,0x1fffffff,
    0x1fffffe4,0xf8ffffff,0xffffffff,0xff75ffff,0x7cc7ffff,0xffd82fff,
    0x20fffd46,0xfffffffd,0xfff50fff,0x205fffff,0xdfffffb8,0xffd91000,
    0x8017dfff,0xefffffdb,0x7fff4c02,0x3ffa004f,0xff9bd102,0x3205ffff,
    0xdfffffff,0x7ffff4c0,0x03ffc81e,0x2000ffd8,0xfffffffb,0x7fff540d,
    0x3ffff21e,0x7ffffe44,0x5fffffff,0x3dffffd3,0xc80effd8,0x0fff83ff,
    0x7fffff5c,0x3fa25fff,0x00efffff,0x80001a88,0x100009a9,0x35100015,
    0x00026000,0x00001353,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x4c400000,0x30099809,0x33333333,0x33330333,
    0x13333333,0x01333330,0x26666620,0x98819999,0x01333009,0x01999988,
    0x31006620,0x26666603,0x01300009,0x000005c4,0x2000002a,0x2601102a,
    0x2002cccb,0x031ccca9,0x3fff2026,0xfffff55f,0x3ffffea1,0x7fffffff,
    0x3fffffea,0x24ffffff,0xfffffffa,0x3ff201df,0x7fffffff,0x2a37fff4,
    0xd06fffff,0x05ffffff,0x209fffd0,0xf52ffff8,0xffffffff,0xfeb8803b,
    0x3ffe85ff,0x0bf50000,0x7ff54000,0xf517fe41,0x5fffffff,0x7fffec40,
    0x7f44ffff,0x7fffec1f,0x3fffff77,0x3ffffff2,0x27ffffff,0xfffffffb,
    0x2e4fffff,0xffffffff,0xfff905ff,0x4fffffff,0x23fffff8,0x07fffffb,
    0xbfffffff,0x7ffff880,0x29ffff70,0xfffffffb,0x3203ffff,0xc87fffff,
    0x0002ffff,0x40003fe4,0x40efffd9,0x3fee5fff,0x0fffffff,0xffffff88,
    0x3e26ffff,0x7fec43ff,0x07ff660a,0x5555ffb3,0xd98ffb55,0xaaaaaaff,
    0x6ffd44ff,0x4fffdbaa,0xaaaaffc8,0x7dc46ffd,0x3ea60fff,0xf55100df,
    0x8801ffff,0xff83ffff,0x7fecc4ff,0xfffdbaaa,0xdadff880,0xfffd501e,
    0x3f20003d,0x3f220007,0xdf703fff,0x7dc1aa83,0xadffd82f,0xc8dff930,
    0x07fc80df,0x1ff20ff7,0x7fb87fb8,0x3fe13fe0,0x41fff883,0x7ffc47fc,
    0x5ffff880,0xf9804ff8,0xe803ffdf,0x7fd46fff,0x07fc82ff,0xff705ff3,
    0xfffb8001,0x7e4001df,0xfff70007,0x4400019f,0x3ff9aaa9,0xfb037fc4,
    0x07fc800b,0x9ff20ff7,0x70df50c9,0xfd8e44ff,0xf303ff82,0x746fb89f,
    0xfff102ff,0x04ff85ff,0x7fd8ffc8,0x2ffffe80,0x20bffffa,0x7ff307fc,
    0x0007ff50,0x033ffff2,0x2003fe40,0x01dffffa,0x7fffdc00,0x7d44ffff,
    0x0072203f,0x3ee0ff90,0x7ecff907,0x9fee02a4,0x3e0515fc,0x11ff603f,
    0x027fec7d,0x1fff7ff1,0x7fc027fc,0xe805ff55,0xff36ffdf,0xff905ffb,
    0x01ffea88,0x20001fff,0x43ffffc8,0xffecccb8,0xea82cccc,0x0002efff,
    0xffffffd8,0x7fdc4fff,0xfc800000,0xfeeeeeef,0xfddff907,0xdff700bf,
    0xff00dffd,0x203fdc07,0x7c405ffb,0x3e5ffabf,0x17fd404f,0xcfe80bff,
    0x9ffd9ffc,0xeffc82ff,0x05ffffee,0x0ccbffd1,0x3fffa600,0xfffffd1f,
    0x3fffffff,0x0fffff62,0x77fdc000,0x4ffa999c,0x00017fd4,0x7ffffe40,
    0xf907ffff,0x00bfffff,0xdffffff7,0x5407ff00,0xdff300ff,0xb3ff8801,
    0x013fe5ff,0x0ffc8ffd,0x3fe33fa0,0x2ff8cffe,0xffffffc8,0xfe884fff,
    0x5ff9afff,0xdfffd300,0x7ffffdc5,0x45ffffff,0x03ffffd8,0xfd97ba60,
    0x44ff980f,0x1cc06ff8,0x3bbff200,0x907feeee,0x0bff99ff,0xfd99ff70,
    0x407ff00d,0xff880ffb,0x7fc4041f,0x3fedff13,0x33bfe604,0x203ffdcc,
    0xffff94fe,0xf905ff11,0xfffb999f,0xfbffd8bf,0x406ffcff,0x03ffffd8,
    0x4c00ff90,0x802efffe,0x3ff22ffb,0xfffda99b,0x37ff60ae,0xffda999a,
    0x32037ae2,0x20ff707f,0x013f67fc,0x25fc9fee,0x203ff82b,0x7ffb06fd,
    0x7fc41fd8,0x3ff3fee3,0x3ffff204,0x207fffff,0xbfff34fe,0x3f20bfe2,
    0x43ffd307,0xffff54ff,0x7ffe440d,0x3f2000cf,0xffea8007,0x17fa01ef,
    0xfffffff1,0x449fffff,0xfffffffe,0x3ffe26ff,0xf707fc83,0xb89ff20f,
    0x5c7fb800,0x7ff0ff30,0x3217fe20,0x43ff85ff,0x7ff43ff8,0x3ffe04ff,
    0xffeeeeee,0x7ec9fd02,0x905ff11f,0x9ffcc0ff,0x3ff23ff8,0xffff703f,
    0xff90001b,0x7ffdc000,0x07fc40df,0x7ffffecc,0x441efffc,0xfffffffc,
    0x417ff40c,0x0ff707fc,0x5c001ff2,0x03fea07f,0xffd107ff,0xf06ffa85,
    0x43ff887f,0x504ffff9,0x2ffc05ff,0x8aa24fe8,0x7fc82ff8,0xfd93fe20,
    0xcfffb9be,0x3bfffa61,0x1ff20001,0xfff91000,0x401fdc7f,0x988001aa,
    0x2a009aaa,0x1bffea80,0x442fffaa,0x1cccffeb,0xccffea80,0x0ffdcccc,
    0x3333bfee,0xff84fffe,0xfcccccdf,0x37fee23f,0x13fff21b,0x1073ffaa,
    0x5417ffd7,0x5c41ceff,0x3aa0cffd,0xdcccccff,0x3fe62fff,0x6fffffff,
    0x000bbffa,0x0001bee0,0xd8fffec4,0x00000006,0x3ffe6000,0xffff77ff,
    0x3ffff2bf,0x2e00ffff,0xffffffff,0xf70fffff,0xffffffff,0xffff10bf,
    0x7fffffff,0x3fffffdc,0xff713ffa,0x7ec1ffff,0xff55ffff,0x7ec1ffff,
    0xff76ffff,0xffffffff,0xfff709ff,0x5c9ffdff,0x2600003e,0x4c00003e,
    0x00002e5d,0x88000000,0xd34ffffd,0x3aa7ffff,0x05ffffff,0x7fffff4c,
    0x0fffffff,0xffffffd3,0x3fe2039b,0xffffffff,0x3fffa63f,0x227fcc4f,
    0x45ffffe9,0x13fffffb,0xa8bffffd,0xd33ffffe,0xffffffff,0x54c405bd,
    0x00000009,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x37975000,
    0x41554401,0x5d402aaa,0x20098bcc,0x9801bca8,0x555441aa,0x2aaaaa60,
    0xa982aaaa,0x4072e62a,0x379732aa,0x101aa980,0xaa981555,0x5555441a,
    0x64cd5440,0x0017950c,0x0aaa8004,0xfd880320,0xffffffff,0x35532eff,
    0x6664aaa2,0x000ceb80,0x7fffffd4,0xffffb82f,0x03ffffa0,0x3fffffa6,
    0xffe885ff,0xfb02ffff,0x3fe69fff,0xfff70fff,0x8fffffff,0xfc9ffffe,
    0x3fa0efff,0xfffffdff,0x9ffffd04,0x1fffff98,0x29fffffd,0x1ffffff9,
    0xfffffff3,0x07ffffdf,0xf8809f30,0x81bee07f,0xfffffffa,0x95ffffff,
    0x5bfe67ff,0x3fe60ffe,0x0fee1eff,0x3ffffff2,0x7fd43fff,0x3fffa0ff,
    0xffffe80f,0x7447ffff,0xffffffff,0x3ffffd82,0x21fffff1,0xfffffffb,
    0x7ffec7ff,0xffffffff,0x3fffff63,0xd82fffff,0x7c43ffff,0xffb0ffff,
    0x3fe27fff,0xff11ffff,0xffffffff,0xf900dfff,0x03ffb80d,0x5409fff5,
    0xcccccccc,0xff50bccc,0x7ed3fe25,0x7fefff47,0x544ffbaf,0xf510afff,
    0xffc881ff,0x207fdc40,0x3660affa,0x37ffa26f,0x20bffaa2,0xff34fffa,
    0x99ffb89f,0x882fffb9,0x51dffffb,0xbfffb81b,0x320bfd30,0x22bd70ff,
    0x7ec40ffd,0x17fec41f,0xff93ffe8,0x900bfe6b,0x06fd80ff,0x07fffff3,
    0x3ff30000,0x27fc9ffc,0xfff52ff9,0xffd81fff,0x70bff301,0x1ff701ff,
    0x21adffa8,0x13fea1c8,0xe982ffc4,0x83fffeff,0x3ffea5f9,0x0fffea02,
    0x5c17fdc0,0x23ff507f,0x0bfd2fff,0xff10ffe6,0xf72ff40b,0x70ffe21f,
    0x95ffb5bf,0x882ff8df,0x2ffebffe,0x33333330,0x7c413333,0x7dcbfa0f,
    0x3fa60d46,0xffff80ef,0xffffffff,0xb80ffb87,0xfffe80ff,0x7e40ceff,
    0x81ff200f,0x02ffffe8,0x805fff50,0x2e002ffa,0x0ffb80ff,0xffabff88,
    0x203ff8df,0x3ff20ffe,0xfb97fa01,0xe87ff10f,0xffffffff,0x20df30ff,
    0xfff33ffe,0x7ffffcc3,0xffffffff,0x23f91fe3,0x066005f9,0x7fffffc4,
    0x0fffffff,0x7dc07fdc,0xfffc880f,0x3fa2ffff,0x00ffd405,0x001dfffb,
    0x5003fff5,0x7dc001ff,0x00ffb80f,0xffffbbfd,0x7d403ff7,0x80bff13f,
    0x43fee5fe,0x7e443ff8,0x1dffffff,0x3fee0bf2,0xf537fd44,0xffffffff,
    0x2f4bffff,0x027c43ee,0x99dff000,0x99999999,0xf701ff70,0x5d44101f,
    0xff90fffd,0x407fec01,0xffffffd8,0x07ffea01,0x0007fd40,0xff701ff7,
    0x3ffff201,0x807ffffd,0x03ff97fe,0x3fee5fe8,0x6c07ff10,0x5d80ffff,
    0x3ee0dfb0,0x2aaaa60f,0x2aaaaaaa,0x3b0a20cc,0x406f5c00,0x70002ffd,
    0xffd881ff,0xf980ff40,0x209ff52f,0xfe885ff9,0x2fffb8df,0x6c1fffa8,
    0x001ff506,0x7dc07fdc,0xffff500f,0x00dfffd3,0x0bff9ff5,0x7fdcbfd0,
    0x2607ff10,0x004fffff,0x035005c4,0x20000000,0xfff881ec,0xbcfff983,
    0x85fdca99,0xfb99cff9,0xff10bfff,0xfb73359f,0x67fff41f,0x42fffdb9,
    0x360ffffa,0xff50cfff,0xff9999df,0x67fee543,0xfb502ccc,0x7fecc17f,
    0x6fff880b,0x2009fff5,0x401ffffe,0xff71effa,0x03bff117,0x3ffd3ffd,
    0x00000000,0x7cc00000,0x01ffe82f,0xfffffff5,0x3fa0ffff,0xffffffff,
    0x3ffffe4f,0x444fffff,0xfffffffe,0x7fffd42f,0xfffff55f,0x3fffff6b,
    0xf72fffff,0xffffffff,0xffff985f,0x3ffffa6f,0x7c7ffd04,0xff5002ff,
    0xfff980bf,0xbfffb8ff,0x7c46fff8,0x007ff12f,0x00000000,0x3fe88000,
    0x7ecc00a8,0x1dffffff,0xbffffd10,0x7e43dffb,0x3ffffffe,0x3ffffb20,
    0xfffe881d,0xdfffd12e,0x3fffff67,0xd32fffff,0xffffffff,0xfffd881d,
    0x3bfff23f,0x641ff901,0x3fa000ff,0x7fec402f,0x13dff75f,0x85507fff,
    0x00000039,0x00000000,0x88000fb1,0x20009aa9,0x440009a8,0x22001aa9,
    0x0000001a,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,
};

static signed short stb__courier_bold_29_usascii_x[95]={ 0,5,3,1,2,1,2,6,6,3,2,1,5,2,
5,2,2,2,1,1,1,1,2,1,2,2,5,5,-1,0,1,2,2,-1,0,0,0,0,1,0,0,2,1,0,
0,-1,-1,0,1,0,0,1,1,0,-1,-1,0,0,1,6,2,3,2,-2,5,1,-1,1,0,0,1,0,0,1,
2,0,1,-1,0,1,-1,0,1,1,1,0,0,-1,0,0,2,4,6,4,1, };
static signed short stb__courier_bold_29_usascii_y[95]={ 21,4,5,3,3,4,6,5,4,4,4,6,17,12,
18,2,4,4,4,4,4,4,4,4,4,4,9,9,6,10,6,5,4,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,4,4,26,3,9,4,9,4,9,4,9,4,4,
4,4,4,9,9,9,9,9,9,9,5,9,9,9,9,9,9,4,4,4,11, };
static unsigned short stb__courier_bold_29_usascii_w[95]={ 0,5,9,13,12,13,13,4,7,6,12,14,6,12,
5,12,12,12,13,13,13,13,12,13,12,12,5,6,16,15,15,12,11,17,15,15,15,15,15,16,15,12,15,16,
15,17,17,15,14,15,16,13,14,16,17,17,16,15,13,7,12,6,12,19,6,14,16,14,16,15,14,16,15,13,
10,15,13,18,15,14,16,16,14,13,15,15,16,17,15,15,12,8,3,8,13, };
static unsigned short stb__courier_bold_29_usascii_h[95]={ 0,18,8,21,22,18,16,8,22,22,12,15,9,3,
4,22,18,17,17,18,17,18,18,18,18,18,13,15,15,8,15,17,20,16,16,17,16,16,16,17,16,16,17,16,
16,16,16,17,16,20,16,17,16,17,16,16,16,16,16,22,22,22,9,3,6,13,18,13,18,13,17,18,17,17,
23,17,17,12,12,13,18,18,12,13,17,13,12,12,12,18,12,22,22,22,6, };
static unsigned short stb__courier_bold_29_usascii_s[95]={ 178,233,225,103,62,206,149,235,88,96,176,
179,189,145,247,41,220,240,212,178,226,192,1,48,79,92,248,211,194,209,163,
67,117,97,133,34,49,33,17,17,1,228,1,193,177,115,79,196,241,129,109,
80,94,50,126,210,160,144,65,54,75,34,196,158,240,218,31,233,62,1,121,
14,105,136,1,150,166,157,106,47,161,239,91,33,180,17,140,122,62,145,78,
25,21,12,240, };
static unsigned short stb__courier_bold_29_usascii_t[95]={ 20,1,79,1,1,1,62,79,1,1,79,
62,79,20,86,1,1,25,25,1,25,1,25,25,25,25,62,62,62,79,62,
44,1,62,62,44,62,62,62,44,62,44,44,44,44,62,62,25,44,1,44,
44,44,44,44,44,44,44,62,1,1,1,79,20,86,62,25,62,25,79,25,
25,25,25,1,25,25,79,79,79,1,1,79,79,25,79,79,79,79,1,79,
1,1,1,79, };
static unsigned short stb__courier_bold_29_usascii_a[95]={ 246,246,246,246,246,246,246,246,
246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,
246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,
246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,
246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,
246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,246,
246,246,246,246,246,246,246, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_courier_bold_29_usascii_BITMAP_HEIGHT or STB_FONT_courier_bold_29_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_courier_bold_29_usascii(stb_fontchar font[STB_FONT_courier_bold_29_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_courier_bold_29_usascii_BITMAP_HEIGHT][STB_FONT_courier_bold_29_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__courier_bold_29_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_courier_bold_29_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_courier_bold_29_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_courier_bold_29_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_courier_bold_29_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_courier_bold_29_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__courier_bold_29_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__courier_bold_29_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__courier_bold_29_usascii_s[i] + stb__courier_bold_29_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__courier_bold_29_usascii_t[i] + stb__courier_bold_29_usascii_h[i]) * recip_height;
            font[i].x0 = stb__courier_bold_29_usascii_x[i];
            font[i].y0 = stb__courier_bold_29_usascii_y[i];
            font[i].x1 = stb__courier_bold_29_usascii_x[i] + stb__courier_bold_29_usascii_w[i];
            font[i].y1 = stb__courier_bold_29_usascii_y[i] + stb__courier_bold_29_usascii_h[i];
            font[i].advance_int = (stb__courier_bold_29_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__courier_bold_29_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__courier_bold_29_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__courier_bold_29_usascii_s[i] + stb__courier_bold_29_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__courier_bold_29_usascii_t[i] + stb__courier_bold_29_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__courier_bold_29_usascii_x[i] - 0.5f;
            font[i].y0f = stb__courier_bold_29_usascii_y[i] - 0.5f;
            font[i].x1f = stb__courier_bold_29_usascii_x[i] + stb__courier_bold_29_usascii_w[i] + 0.5f;
            font[i].y1f = stb__courier_bold_29_usascii_y[i] + stb__courier_bold_29_usascii_h[i] + 0.5f;
            font[i].advance = stb__courier_bold_29_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_courier_bold_29_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_courier_bold_29_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_courier_bold_29_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_courier_bold_29_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_courier_bold_29_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_courier_bold_29_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_courier_bold_29_usascii_LINE_SPACING
#endif

