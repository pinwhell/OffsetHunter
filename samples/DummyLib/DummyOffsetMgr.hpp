#pragma once

#include <json/json.h>
#include <cstdint>

struct OffMgr {
#if defined(STATIC_OFFS)
#if defined(ARM64)
	struct BinArm64A {
		uintptr_t name1 = 0x8;	 // Should be 0x8 #(Hi)#
		uintptr_t name2 = 0x8;	 // Should be 0x8
		uintptr_t name3 = 0x8;	 // Should be 0x8
	} mBinArm64A;
#endif

#else

#if defined(ARM64)
	struct BinArm64A {
		uintptr_t name1;	 // Should be 0x8 #(Hi)#
		uintptr_t name2;	 // Should be 0x8
		uintptr_t name3;	 // Should be 0x8
	} mBinArm64A;
#endif

	void Set(const Json::Value& obj) {
	static bool decrypted = false;

	if(decrypted) return;

#if defined(ARM64)
	mBinArm64A.name1 = obj["462494170"].asUInt();	 // Should be 0x8 #(Hi)#
	mBinArm64A.name2 = obj["4119764849"].asUInt();	 // Should be 0x8
	mBinArm64A.name3 = obj["3482068232"].asUInt();	 // Should be 0x8
#endif


	decrypted = true;
	}
#endif

} ;
extern OffMgr *gOffMgrOffs;
