// Font generated by stb_font_inl_generator.c (4/1 bpp)
//
// Following instructions show how to use the only included font, whatever it is, in
// a generic way so you can replace it with any other font by changing the include.
// To use multiple fonts, replace STB_SOMEFONT_* below with STB_FONT_courier_20_usascii_*,
// and separately install each font. Note that the CREATE function call has a
// totally different name; it's just 'stb_font_courier_20_usascii'.
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

#define STB_FONT_courier_20_usascii_BITMAP_WIDTH         256
#define STB_FONT_courier_20_usascii_BITMAP_HEIGHT         52
#define STB_FONT_courier_20_usascii_BITMAP_HEIGHT_POW2    64

#define STB_FONT_courier_20_usascii_FIRST_CHAR            32
#define STB_FONT_courier_20_usascii_NUM_CHARS             95

#define STB_FONT_courier_20_usascii_LINE_SPACING           9

static unsigned int stb__courier_20_usascii_pixels[]={
    0x1c0e4110,0x904ca0ae,0x98e02800,0x27740401,0x80c40e20,0x000005ec,
    0x20000000,0x1bcb89a9,0x2aa59710,0x00000880,0x25513793,0x0aaa0aa9,
    0x0c40bb10,0x71003ea8,0x00662057,0x2a48585b,0x1b86eb02,0xb301b100,
    0x1d993068,0x440c802c,0x8b03dbcd,0x1aa0ddd9,0x6d426edc,0x6ee440cd,
    0x1cccb880,0x2a2f76a2,0x64ce642d,0x809501dc,0xda8cc805,0x883d10cc,
    0xb10b002c,0x09109979,0x6e40a8e0,0x83701dca,0x2019240b,0x402c4195,
    0x361edbcc,0x89261e41,0x21620165,0x12c2540d,0x47a9621d,0x892602d8,
    0xb85886c5,0x03f11621,0x1b20e61d,0x202c0298,0x1543e839,0x3b0b002c,
    0x802443a8,0x0b0b0663,0x0c9205c0,0x803212b0,0x86885c2a,0x0b2c2c68,
    0xb03b8390,0x39072581,0xc803b1a6,0x5c298dc0,0x1a22a803,0x6880c954,
    0x55d53000,0x3b824155,0xca815c58,0xb03b8b1c,0x02caa443,0x90109155,
    0x85555511,0x8819240b,0x2209d9d9,0x4b806e04,0x3622c3d0,0xe85880b0,
    0x1a587700,0x09134ce6,0x191c8190,0x44390090,0x44125505,0x101aa986,
    0x583333b3,0x2c550770,0x5bc99cc8,0x223a80ec,0x82da8bdc,0xac075129,
    0x20d99998,0xc81b241b,0x643ceced,0x9015b100,0xb244b607,0x370161b7,
    0x962440b0,0x54b34885,0x27660551,0xd50ea5a8,0xf10f6a20,0x5c1ccb01,
    0x40499886,0x1f415405,0x07505558,0x962068d9,0xa88581f8,0x05d500bb,
    0xa45d1064,0x4167304d,0x1ee4c049,0xa44f205b,0xb016191b,0x2c488160,
    0xc962910b,0xb80dabd9,0x47620fef,0x3b7305c9,0x7932dd88,0x5db88bd8,
    0x20160240,0x03cc98bd,0x20360b55,0x4b103469,0x2e237068,0x012a010b,
    0x8a44a832,0x1d9bb885,0x4ae001b0,0x5225b02d,0xa816190c,0x0ee01902,
    0x58a442cb,0x543883ae,0x6441b30c,0x43900b3d,0x00bdb8c8,0x90167b93,
    0x9b300580,0x81740733,0x203b1a05,0x1cc1623a,0x0cc255c4,0x48370640,
    0xcddc9832,0x183982ce,0x3a099398,0x36f62911,0x7502c0b1,0x42cb03a0,
    0x5839823a,0x1201542c,0x00489220,0xb01202c0,0x580a6000,0x71aa0720,
    0x0f887609,0x0a2380c8,0x81706400,0x226e0324,0x10fc2c04,0x2341661b,
    0x505854c6,0x2542d807,0x02c81b2c,0x9858b0b1,0x2200ae03,0xb0001224,
    0x04240480,0x02a80e40,0x86d88366,0x3a21d42d,0x223824c4,0x06401dc2,
    0x20324817,0x1540489b,0xd07776f2,0x006c4a81,0x75c0160b,0x254b03db,
    0x8321ccb3,0x81615439,0x3205444b,0x0035b730,0x900aeaa8,0xcdcbd980,
    0x21ed5540,0x200aeaa9,0xde8ecce9,0x2265f6c0,0xbdceacea,0x98957100,
    0x906400ff,0x3206e481,0x20580398,0x40e87704,0x985860d9,0x085b3003,
    0x83736e2c,0x1e66c1fc,0x2a2dcdb8,0xbd703dcb,0x555445b9,0x15554001,
    0xbddfddd1,0x55500c40,0x15555101,0x22001100,0x08006001,0x21900110,
    0x0762484b,0x0ae00a69,0x824cb024,0x2ba3ddfb,0x3a600362,0x552eddcd,
    0x4020110d,0x02201000,0x00000440,0x00000000,0x00000000,0x00000000,
    0x20201340,0x50180000,0x20001040,0x00006099,0x00001988,0x00000000,
    0x00000000,0x00000000,0x00000000,0x75510000,0x0000003d,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0xd8813551,0xdddddddd,0x0000000d,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x2a000000,
    0x3a25eeee,0x002eeeee,0x00c00c40,0x00062000,0x00000000,0x17620000,
    0x073b6a00,0x00000000,0x00000000,0x80000000,0x2f7b21ec,0x07100d40,
    0x433b6255,0x33223eca,0x37224bcb,0xcb81dccb,0x3620ccec,0x320cbcbc,
    0x54bb223e,0x377264ce,0x64479d70,0x88fb61dd,0x333362fc,0x2002c2dc,
    0xcec9842b,0x33361ccc,0x952dccec,0xa9f6541f,0x70de985e,0x910199d9,
    0x8bf6259d,0x2dcccec8,0x599d9990,0xdda8e754,0x88b63f91,0x64000d45,
    0x322c0e20,0x883b2640,0x6c06401e,0x0720fc40,0x0aa05839,0x36032037,
    0x36160e40,0x016002c0,0x922cb116,0x1617622a,0x82bc837b,0x0d88b005,
    0x480390b0,0xfb8e6160,0x2a1b8388,0x1c458001,0xb9442c58,0x0c801302,
    0x440b815c,0x5a961265,0xb109106a,0x41d43620,0xcbac0e45,0xaaeaa80b,
    0xb398581a,0xbc88aa48,0x896362c1,0xb00582ac,0x20b006cc,0x30b02404,
    0x8aa03d47,0x401ddeda,0x4581c439,0x0001200b,0xa8004819,0x664320b3,
    0x550b0171,0x082c64c0,0x456ec126,0x4ecc40d9,0x39858099,0x48826485,
    0x70cac58b,0x200b0553,0x30b00b35,0x21604807,0x5881a639,0x401910c4,
    0x4581c40c,0x02c1bcb8,0x00b03200,0x8dc07320,0x0aa0939d,0x801d700b,
    0x55076058,0xb3160160,0x54881201,0x5a4562c7,0x3600b055,0x99d803ea,
    0x204804ca,0x43dccccd,0x26003601,0x40e21603,0x2c76a205,0x80caaaa2,
    0x88002c0c,0xace6aa05,0x80489605,0x00e401dc,0x0160730b,0x8033733a,
    0xb0d92204,0x154ab258,0xb74d802c,0x04daad80,0x4ccec090,0x1d8803a9,
    0x41c41600,0x5600b038,0x4b26620d,0x0ec0c81b,0x2a604800,0x640b191b,
    0xb3a80190,0x5870ea01,0xb00b0398,0x92204800,0x9e658b48,0x4488582a,
    0xb8b01d45,0x21604804,0x00ec4039,0x406e0530,0x40aa3886,0x5c6e0775,
    0x204a8481,0x5b881200,0xb48816aa,0x21624980,0x4c2c5858,0x00b00b03,
    0x39122048,0x20aa058b,0x2c2c4885,0x480570b0,0x880e6160,0xd819100d,
    0x21640b00,0x8ea1aa0c,0x8771b81d,0xd885b039,0x4bb01201,0x156c04d8,
    0x44a81b10,0x4c2c580d,0x00b00b03,0x36122048,0xb05502c5,0x2a858910,
    0x090160b0,0xd881cc2c,0x9bd50440,0xb012203b,0xeba8597b,0x7ec44dbd,
    0x36a0cdbc,0x3f200bcb,0xee980dcb,0xe85d05ef,0x8807d403,0x53fa24ee,
    0x5eeeeef8,0x775437f6,0x3bbbfb63,0x0bbbfa61,0x22f7f74c,0x9aa1efe8,
    0x776c3efb,0xddddfd91,0x0fbf629d,0x1f7ec4bd,0xfeed87a6,0x47bf62ee,
    0xeeb83eeb,0x0883eeee,0x00110000,0x80330011,0x0004c001,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x0009b100,0x00000000,0x99300000,0x7dd50180,0x0143d300,0x01804c00,
    0x0e5c414c,0xacb98298,0x032ca808,0x6544072a,0x542a882c,0x502aa61a,
    0x7972a855,0x2e615501,0xca9dcaa2,0x55555541,0x765402c0,0x915ccccc,
    0x4b99999d,0x84dccdea,0x100eecc8,0x07b999d9,0x3620937b,0x201201db,
    0x00b6a2ad,0x24033220,0x9cc8ffa0,0x1ff40cb8,0x45d51395,0x47c98ad9,
    0x40db8adb,0x984a88ab,0x3b11d4c5,0x6c42c881,0x4c0d98ad,0x12a9cbaa,
    0x919b71bb,0x74cccec1,0x048802c1,0x0b8b058b,0x073b02cc,0x1202b858,
    0x4048005c,0x1db82aab,0x4803b700,0x8398edc0,0x1b0edc39,0x23412198,
    0x04804884,0x11a8730b,0x541d82c7,0x3602e982,0x90e2a9a0,0x05554b03,
    0x4161c122,0x415c05c3,0xb0580b39,0x001b8240,0x02aac409,0x36a01991,
    0xc8009001,0x04999999,0x441acd98,0x0901a803,0xb01b7971,0xd7388730,
    0x1cc2c161,0x4b1601cc,0x9605702a,0x0e4881dc,0x05c06a58,0x0370c858,
    0x0901d42c,0x90240162,0x9b100aa3,0x5300b661,0x01555b75,0xaaaaaad8,
    0x372a2002,0x01900350,0x999bd86e,0x8398580d,0x209175b5,0x02983985,
    0xa82a962c,0x101dd603,0x66c0d99d,0x201701dc,0xd8122585,0x2405eccc,
    0x01996e44,0x02a92609,0x07b31ecc,0xaadbaa98,0x05526442,0x8a4c0400,
    0x4b039804,0x8580c81b,0x5b48d839,0x20e61605,0xa962c029,0xbb022542,
    0x599c8807,0x40726760,0x42a8b00b,0x26667605,0x46e1204b,0x6c1203b5,
    0x66440aa0,0x2005b500,0x1b0fee04,0x997ec150,0x20723985,0x4570361b,
    0x5c07d41b,0x32e0fa20,0x21601991,0x2c029839,0x21662a96,0x1006d744,
    0x844b00c9,0x224405c0,0x02dccccd,0x4240aa0b,0x84813265,0x1eeeeef8,
    0xdb800edc,0x0db02401,0x85b97971,0x797b13fe,0xcbdb889b,0x6e6dc42c,
    0x4dde6c42,0x65ec42ec,0x334c2e9a,0x4437f60f,0xddb932ee,0x3e5fb8bd,
    0x3bba3d53,0xd8ac4eee,0x16009100,0x570170dc,0x0b058244,0x0d4240e6,
    0xa802405d,0x200076a2,0x20900cc8,0x004c01f8,0x00c00c01,0x00044008,
    0x00000003,0x00000000,0x4880d896,0xb86e0b00,0x406e1d40,0x03b0580c,
    0x756e6412,0x8aa00903,0x00880002,0x00012603,0x00000000,0x00000000,
    0x00000000,0x226d8800,0x3bbaa5fe,0xeefd881e,0xdd51eeee,0xefc87bdd,
    0x447bb623,0x1deeeefd,0x1777f76c,0x7f774c02,0xeed884ee,0x00000001,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x55315544,0x530aa985,0x32207015,0xc9654004,0x3776060c,
    0x4c2ddddd,0x2eee6000,0x00003bbb,0x00000000,0x00000000,0x00000000,
    0x00000000,0x36620000,0xb1076621,0x0481e445,0x212209f5,0x641fd2fb,
    0x36f20002,0x732fd8e2,0x00777777,0x00000000,0x00000000,0x00000000,
    0x00000000,0xb0000000,0x3b102b81,0x232570ee,0x6c03f62b,0x7d8fd43b,
    0x222223b8,0xc8620888,0x00bfa1dc,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x20161cc0,0xfdb882cd,0x1c827c2c,0x6c87cc39,
    0x66666410,0x40202ccc,0x00000001,0x00000000,0x00000000,0x00000000,
    0x00000000,0x732c0000,0x6c03b900,0x5c07cc2c,0x2a7886c2,0x00000004,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x36550000,
    0x81c96400,0x80c41b2b,0x00002883,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x2c8091b0,0x01886164,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x6ff401d7,0x0007fd50,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,
};

static signed short stb__courier_20_usascii_x[95]={ 0,4,2,1,1,1,2,4,5,2,0,1,2,1,
3,1,1,1,1,1,1,1,2,1,1,2,3,2,0,0,0,0,1,0,0,1,1,0,1,1,0,1,1,0,
1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,0,3,1,0,1,1,1,1,1,0,1,
1,1,1,0,0,1,0,1,1,1,1,0,0,0,0,1,2,0,4,0,1, };
static signed short stb__courier_20_usascii_y[95]={ 14,2,3,2,2,3,4,3,3,3,3,4,11,8,
11,2,2,3,2,2,3,3,2,3,2,2,6,6,4,7,4,3,2,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,2,18,2,6,3,6,3,6,3,6,3,2,
2,3,3,6,6,6,6,6,6,6,3,6,6,6,6,6,6,3,3,3,7, };
static unsigned short stb__courier_20_usascii_w[95]={ 0,3,7,8,8,8,7,3,4,4,7,9,5,8,
4,8,8,8,8,8,8,8,8,8,8,8,4,5,9,10,9,7,8,11,10,9,9,10,9,9,10,8,10,11,
9,11,10,9,9,10,11,8,9,10,11,11,10,10,8,3,7,3,8,12,4,9,10,9,10,9,9,9,10,9,
7,10,8,11,10,9,10,10,9,8,9,10,11,11,10,10,7,4,2,4,8, };
static unsigned short stb__courier_20_usascii_h[95]={ 0,13,6,14,14,12,11,6,14,14,7,10,6,2,
4,14,13,11,12,13,11,12,13,12,13,13,9,10,10,4,10,12,14,11,11,12,11,11,11,12,11,11,12,11,
11,11,11,12,11,14,11,12,11,12,11,11,11,11,11,14,14,14,6,1,4,9,12,9,12,9,11,12,11,12,
16,11,11,8,8,9,12,12,8,9,12,9,8,9,8,12,8,14,14,14,4, };
static unsigned short stb__courier_20_usascii_s[95]={ 144,104,147,22,39,239,75,252,48,53,124,
121,132,185,180,71,95,66,1,135,92,10,108,19,117,126,147,131,111,160,101,
248,58,43,55,69,33,22,12,48,241,232,58,208,198,186,175,218,155,80,220,
39,165,28,102,90,114,79,125,67,31,91,138,9,155,181,228,161,207,137,145,
186,134,166,1,1,83,235,214,171,144,155,225,152,176,191,101,202,113,196,247,
17,14,9,171, };
static unsigned short stb__courier_20_usascii_t[95]={ 14,1,42,1,1,1,31,18,1,1,42,
31,42,42,42,1,1,31,18,1,31,18,1,18,1,1,31,31,31,42,31,
1,1,31,31,18,31,31,31,18,18,18,18,18,18,18,18,1,18,1,18,
18,18,18,18,18,18,18,18,1,1,1,42,16,42,31,1,31,1,31,18,
1,18,1,1,31,31,31,31,31,1,1,31,31,1,31,42,31,42,1,31,
1,1,1,42, };
static unsigned short stb__courier_20_usascii_a[95]={ 170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170, };

// Call this function with
//    font: NULL or array length
//    data: NULL or specified size
//    height: STB_FONT_courier_20_usascii_BITMAP_HEIGHT or STB_FONT_courier_20_usascii_BITMAP_HEIGHT_POW2
//    return value: spacing between lines
static void stb_font_courier_20_usascii(stb_fontchar font[STB_FONT_courier_20_usascii_NUM_CHARS],
                unsigned char data[STB_FONT_courier_20_usascii_BITMAP_HEIGHT][STB_FONT_courier_20_usascii_BITMAP_WIDTH],
                int height)
{
    int i,j;
    if (data != 0) {
        unsigned int *bits = stb__courier_20_usascii_pixels;
        unsigned int bitpack = *bits++, numbits = 32;
        for (i=0; i < STB_FONT_courier_20_usascii_BITMAP_WIDTH*height; ++i)
            data[0][i] = 0;  // zero entire bitmap
        for (j=1; j < STB_FONT_courier_20_usascii_BITMAP_HEIGHT-1; ++j) {
            for (i=1; i < STB_FONT_courier_20_usascii_BITMAP_WIDTH-1; ++i) {
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
        float recip_width = 1.0f / STB_FONT_courier_20_usascii_BITMAP_WIDTH;
        float recip_height = 1.0f / height;
        for (i=0; i < STB_FONT_courier_20_usascii_NUM_CHARS; ++i) {
            // pad characters so they bilerp from empty space around each character
            font[i].s0 = (stb__courier_20_usascii_s[i]) * recip_width;
            font[i].t0 = (stb__courier_20_usascii_t[i]) * recip_height;
            font[i].s1 = (stb__courier_20_usascii_s[i] + stb__courier_20_usascii_w[i]) * recip_width;
            font[i].t1 = (stb__courier_20_usascii_t[i] + stb__courier_20_usascii_h[i]) * recip_height;
            font[i].x0 = stb__courier_20_usascii_x[i];
            font[i].y0 = stb__courier_20_usascii_y[i];
            font[i].x1 = stb__courier_20_usascii_x[i] + stb__courier_20_usascii_w[i];
            font[i].y1 = stb__courier_20_usascii_y[i] + stb__courier_20_usascii_h[i];
            font[i].advance_int = (stb__courier_20_usascii_a[i]+8)>>4;
            font[i].s0f = (stb__courier_20_usascii_s[i] - 0.5f) * recip_width;
            font[i].t0f = (stb__courier_20_usascii_t[i] - 0.5f) * recip_height;
            font[i].s1f = (stb__courier_20_usascii_s[i] + stb__courier_20_usascii_w[i] + 0.5f) * recip_width;
            font[i].t1f = (stb__courier_20_usascii_t[i] + stb__courier_20_usascii_h[i] + 0.5f) * recip_height;
            font[i].x0f = stb__courier_20_usascii_x[i] - 0.5f;
            font[i].y0f = stb__courier_20_usascii_y[i] - 0.5f;
            font[i].x1f = stb__courier_20_usascii_x[i] + stb__courier_20_usascii_w[i] + 0.5f;
            font[i].y1f = stb__courier_20_usascii_y[i] + stb__courier_20_usascii_h[i] + 0.5f;
            font[i].advance = stb__courier_20_usascii_a[i]/16.0f;
        }
    }
}

#ifndef STB_SOMEFONT_CREATE
#define STB_SOMEFONT_CREATE              stb_font_courier_20_usascii
#define STB_SOMEFONT_BITMAP_WIDTH        STB_FONT_courier_20_usascii_BITMAP_WIDTH
#define STB_SOMEFONT_BITMAP_HEIGHT       STB_FONT_courier_20_usascii_BITMAP_HEIGHT
#define STB_SOMEFONT_BITMAP_HEIGHT_POW2  STB_FONT_courier_20_usascii_BITMAP_HEIGHT_POW2
#define STB_SOMEFONT_FIRST_CHAR          STB_FONT_courier_20_usascii_FIRST_CHAR
#define STB_SOMEFONT_NUM_CHARS           STB_FONT_courier_20_usascii_NUM_CHARS
#define STB_SOMEFONT_LINE_SPACING        STB_FONT_courier_20_usascii_LINE_SPACING
#endif

