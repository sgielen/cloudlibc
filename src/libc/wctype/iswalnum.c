// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <wctype.h>

#include "wctype_impl.h"

int iswalnum(wint_t wc) {
  static const uint32_t extents[] = {
      0x00018009, 0x00020819, 0x00030819, 0x00055000, 0x00059001, 0x0005a800,
      0x0005c801, 0x0005e002, 0x00060016, 0x0006c01e, 0x0007c1c9, 0x0016300b,
      0x00170004, 0x00176000, 0x00177000, 0x001a2800, 0x001b8004, 0x001bb001,
      0x001bd003, 0x001bf800, 0x001c3000, 0x001c4002, 0x001c6000, 0x001c7013,
      0x001d1852, 0x001fb88a, 0x002450a5, 0x00298825, 0x002ac800, 0x002b0826,
      0x002e801a, 0x002f8002, 0x0031002a, 0x00330009, 0x00337001, 0x00338862,
      0x0036a800, 0x00372801, 0x0037700e, 0x0037f800, 0x00388000, 0x0038901d,
      0x003a6858, 0x003d8800, 0x003e002a, 0x003fa001, 0x003fd000, 0x00400015,
      0x0040d000, 0x00412000, 0x00414000, 0x00420018, 0x00450012, 0x00482035,
      0x0049e800, 0x004a8000, 0x004ac009, 0x004b3009, 0x004b880f, 0x004c2807,
      0x004c7801, 0x004c9815, 0x004d5006, 0x004d9000, 0x004db003, 0x004de800,
      0x004e7000, 0x004ee001, 0x004ef802, 0x004f300b, 0x004fa005, 0x00502805,
      0x00507801, 0x00509815, 0x00515006, 0x00519001, 0x0051a801, 0x0051c001,
      0x0052c803, 0x0052f000, 0x00533009, 0x00539002, 0x00542808, 0x00547802,
      0x00549815, 0x00555006, 0x00559001, 0x0055a804, 0x0055e800, 0x00568000,
      0x00570001, 0x00573009, 0x00582807, 0x00587801, 0x00589815, 0x00595006,
      0x00599001, 0x0059a804, 0x0059e800, 0x005ae001, 0x005af802, 0x005b3009,
      0x005b8806, 0x005c1800, 0x005c2805, 0x005c7002, 0x005c9003, 0x005cc801,
      0x005ce000, 0x005cf001, 0x005d1801, 0x005d4002, 0x005d700b, 0x005e8000,
      0x005f300c, 0x00602807, 0x00607002, 0x00609016, 0x0061500f, 0x0061e800,
      0x0062c001, 0x00630001, 0x00633009, 0x0063c006, 0x00642807, 0x00647002,
      0x00649016, 0x00655009, 0x0065a804, 0x0065e800, 0x0066f000, 0x00670001,
      0x00673009, 0x00678801, 0x00682807, 0x00687002, 0x00689028, 0x0069e800,
      0x006a7000, 0x006b0001, 0x006b300f, 0x006bd005, 0x006c2811, 0x006cd017,
      0x006d9808, 0x006de800, 0x006e0006, 0x006f3009, 0x0070082f, 0x00719001,
      0x00720006, 0x00728009, 0x00740801, 0x00742000, 0x00743801, 0x00745000,
      0x00746800, 0x0074a003, 0x0074c806, 0x00750802, 0x00752800, 0x00753800,
      0x00755001, 0x00756803, 0x00759001, 0x0075e800, 0x00760004, 0x00763000,
      0x00768009, 0x0076e003, 0x00780000, 0x00790013, 0x007a0007, 0x007a4823,
      0x007c4004, 0x0080002a, 0x0081f80a, 0x00828005, 0x0082d003, 0x00830800,
      0x00832801, 0x00837002, 0x0083a80c, 0x00847000, 0x00848009, 0x00850025,
      0x00863800, 0x00866800, 0x0086802a, 0x0087e14c, 0x00925003, 0x00928006,
      0x0092c000, 0x0092d003, 0x00930028, 0x00945003, 0x00948020, 0x00959003,
      0x0095c006, 0x00960000, 0x00961003, 0x0096400e, 0x0096c038, 0x00989003,
      0x0098c042, 0x009b4813, 0x009c000f, 0x009d0054, 0x00a00a6b, 0x00b37810,
      0x00b40819, 0x00b5004a, 0x00b7700a, 0x00b8000c, 0x00b87003, 0x00b90011,
      0x00ba0011, 0x00bb000c, 0x00bb7002, 0x00bc0033, 0x00beb800, 0x00bee000,
      0x00bf0009, 0x00bf8009, 0x00c08009, 0x00c10057, 0x00c40028, 0x00c55000,
      0x00c58045, 0x00c8001e, 0x00ca3027, 0x00cb8004, 0x00cc002b, 0x00ce0806,
      0x00ce800a, 0x00d00016, 0x00d10034, 0x00d40009, 0x00d48009, 0x00d53800,
      0x00d8282e, 0x00da2806, 0x00da8009, 0x00dc181d, 0x00dd7037, 0x00e00023,
      0x00e20009, 0x00e26830, 0x00e74803, 0x00e77003, 0x00e7a801, 0x00e800bf,
      0x00f00115, 0x00f8c005, 0x00f90025, 0x00fa4005, 0x00fa8007, 0x00fac800,
      0x00fad800, 0x00fae800, 0x00faf81e, 0x00fc0034, 0x00fdb006, 0x00fdf000,
      0x00fe1002, 0x00fe3006, 0x00fe8003, 0x00feb005, 0x00ff000c, 0x00ff9002,
      0x00ffb006, 0x01038001, 0x0103a005, 0x0103f80a, 0x0104800c, 0x01081000,
      0x01083800, 0x01085009, 0x0108a800, 0x0108c804, 0x01092000, 0x01093000,
      0x01094005, 0x0109780a, 0x0109e003, 0x010a2804, 0x010a7000, 0x010a8039,
      0x0123009f, 0x013bb01d, 0x0160002e, 0x0161802e, 0x01630084, 0x01675803,
      0x01679001, 0x0167e800, 0x01680025, 0x01693800, 0x01696800, 0x01698037,
      0x016b7800, 0x016c0016, 0x016d0006, 0x016d4006, 0x016d8006, 0x016dc006,
      0x016e0006, 0x016e4006, 0x016e8006, 0x016ec006, 0x01717800, 0x01802802,
      0x01810808, 0x01818804, 0x0181c004, 0x01820855, 0x0184e802, 0x01850859,
      0x0187e003, 0x01882828, 0x0189885d, 0x018c9003, 0x018d001a, 0x018f800f,
      0x01910009, 0x01924007, 0x0192880e, 0x01940009, 0x0195880e, 0x01a00000,
      0x026da800, 0x02700000, 0x04fe6000, 0x0500048c, 0x0526802d, 0x0528010c,
      0x0530801b, 0x0532002e, 0x0533f81e, 0x0535004f, 0x0538b808, 0x05391066,
      0x053c5803, 0x053c801d, 0x053d8001, 0x053fb80a, 0x05401802, 0x05403803,
      0x05406016, 0x05418005, 0x05420033, 0x05441031, 0x05468009, 0x05479005,
      0x0547d800, 0x05480025, 0x05498016, 0x054b001c, 0x054c202e, 0x054e780a,
      0x054f0004, 0x054f3018, 0x05500028, 0x05520002, 0x05522007, 0x05528009,
      0x05530016, 0x0553d000, 0x0553f031, 0x05558800, 0x0555a801, 0x0555c804,
      0x05560000, 0x05561000, 0x0556d802, 0x0557000a, 0x05579002, 0x05580805,
      0x05584805, 0x05588805, 0x05590006, 0x05594006, 0x0559802a, 0x055ae003,
      0x055b2001, 0x055e0022, 0x055f8009, 0x05600000, 0x06bd1800, 0x06bd8016,
      0x06be5830, 0x07c8016d, 0x07d38069, 0x07d80006, 0x07d89804, 0x07d8e800,
      0x07d8f809, 0x07d9500c, 0x07d9c004, 0x07d9f000, 0x07da0001, 0x07da1801,
      0x07da306b, 0x07de996a, 0x07ea803f, 0x07ec9035, 0x07ef800b, 0x07f38004,
      0x07f3b086, 0x07f88009, 0x07f90819, 0x07fa0819, 0x07fb3058, 0x07fe1005,
      0x07fe5005, 0x07fe9005, 0x07fed002, 0x0800000b, 0x08006819, 0x08014012,
      0x0801e001, 0x0801f80e, 0x0802800d, 0x0804007a, 0x0808382c, 0x080a0038,
      0x080c5001, 0x0814001c, 0x08150030, 0x0817081a, 0x08180023, 0x0819801a,
      0x081a8025, 0x081c001d, 0x081d0023, 0x081e4007, 0x081e8804, 0x0820009d,
      0x08250009, 0x08280027, 0x08298033, 0x08300136, 0x083a0015, 0x083b0007,
      0x08400005, 0x08404000, 0x0840502b, 0x0841b801, 0x0841e000, 0x0841f816,
      0x0842c01e, 0x0843c825, 0x08453808, 0x0848001b, 0x08490019, 0x084c0037,
      0x084df001, 0x08500000, 0x08508003, 0x0850a802, 0x0850c81a, 0x08520007,
      0x0853001e, 0x0854001f, 0x08560007, 0x0856481b, 0x08575804, 0x08580035,
      0x085a0015, 0x085ac01a, 0x085bc019, 0x085d4806, 0x08600048, 0x0873001e,
      0x08801834, 0x0882901d, 0x0884182c, 0x08868018, 0x08878009, 0x08881823,
      0x0889b009, 0x088a8022, 0x088bb000, 0x088c182f, 0x088e0803, 0x088e800a,
      0x088f0813, 0x08900011, 0x08909818, 0x0895802e, 0x08978009, 0x08982807,
      0x08987801, 0x08989815, 0x08995006, 0x08999001, 0x0899a804, 0x0899e800,
      0x089ae804, 0x08a4002f, 0x08a62001, 0x08a63800, 0x08a68009, 0x08ac002e,
      0x08b0002f, 0x08b22000, 0x08b28009, 0x08b4002a, 0x08b60009, 0x08c50052,
      0x08c7f800, 0x08d60038, 0x09000398, 0x0920006e, 0x0980042e, 0x0b400238,
      0x0b52001e, 0x0b530009, 0x0b56801d, 0x0b58002f, 0x0b5a0003, 0x0b5a8009,
      0x0b5ad806, 0x0b5b1814, 0x0b5be812, 0x0b780044, 0x0b7a8000, 0x0b7c980c,
      0x0d800001, 0x0de0006a, 0x0de3800c, 0x0de40008, 0x0de48009, 0x0e9b0011,
      0x0ea00054, 0x0ea2b046, 0x0ea4f001, 0x0ea51000, 0x0ea52801, 0x0ea54803,
      0x0ea5700b, 0x0ea5d800, 0x0ea5e806, 0x0ea62840, 0x0ea83803, 0x0ea86807,
      0x0ea8b006, 0x0ea8f01b, 0x0ea9d803, 0x0eaa0004, 0x0eaa3000, 0x0eaa5006,
      0x0eaa9153, 0x0eb54018, 0x0eb61018, 0x0eb6e01e, 0x0eb7e018, 0x0eb8b01e,
      0x0eb9b018, 0x0eba801e, 0x0ebb8018, 0x0ebc501e, 0x0ebd5018, 0x0ebe2007,
      0x0ebe7031, 0x0f4000c4, 0x0f463808, 0x0f700003, 0x0f70281a, 0x0f710801,
      0x0f712000, 0x0f713800, 0x0f714809, 0x0f71a003, 0x0f71c800, 0x0f71d800,
      0x0f721000, 0x0f723800, 0x0f724800, 0x0f725800, 0x0f726802, 0x0f728801,
      0x0f72a000, 0x0f72b800, 0x0f72c800, 0x0f72d800, 0x0f72e800, 0x0f72f800,
      0x0f730801, 0x0f732000, 0x0f733803, 0x0f736006, 0x0f73a003, 0x0f73c803,
      0x0f73f000, 0x0f740009, 0x0f745810, 0x0f750802, 0x0f752804, 0x0f755810,
      0x0f88000c, 0x0f88801c, 0x0f898019, 0x0f8a8019, 0x0f8b801a, 0x0f8f3019,
      0x10000000, 0x1536b000, 0x15380000, 0x15b9a000, 0x15ba0000, 0x15c0e800,
      0x17c0021d,
  };
  return iswctype_extents(wc, extents, __arraycount(extents));
}
