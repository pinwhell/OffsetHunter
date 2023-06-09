#pragma once

#include "IFutureResultInfo.h"
#include "JsonValueWrapper.h"
#include "IChild.h"
#include "IJsonAccesor.h"

class SingleDumpTarget;
class TargetManager;
struct HeaderFileManager;
class ICapstoneHelper;
class ObfuscationManager;

enum class ResultState {
	NOT_STARTED,
	IN_PROGRESS,
	FINISH_SUCESS,
	FINISH_INVALID
};

class IFutureResult : public IChild<SingleDumpTarget>
{
protected:

	// the buffer info i will be finded on
	const char* mBuffer;
	size_t mBuffSize;
	TargetManager* mTargetMgr;
	bool mNeedCapstone;
	JsonValueWrapper mObfuscationData;
	JsonValueWrapper mMetadata;
	bool bFinishComputing;
	std::atomic<ResultState> mResultState;
	IFutureResultInfo* mpFutureResultInfo;

public:

	IFutureResult();

	virtual bool Init();
	virtual void Compute();
	std::string getName();
	std::string getSignature();
	void ReportHppIncludes();
	void WriteHppStaticDeclsDefs(); // This structs arround need to be refactored to handle general stuffs, not just offsets,
	void WriteHppDynDecls(); // Code structure is done, just refactoring names, and key specific structures
	void WriteHppDynDefs();

	void setTargetManager(TargetManager* pTarget);
	TargetManager* getTargetManager();

	IJsonAccesor* getJsonAccesor();
	bool getDumpDynamic();

	void setMetadata(const JsonValueWrapper& metadata);
	JsonValueWrapper& getMetadata();

	void setBufferInfo(const char* buff, size_t buffSz);

	HeaderFileManager* getHppWriter();

	bool getNeedCapstoneHelper();
	ICapstoneHelper* getCapstoneHelper();
	JsonValueWrapper* getResultJson();
	ObfuscationManager* getObfuscationManager();

	IFutureResultInfo* getFutureResultInfo();

	virtual void OnParentTargetFinish();
	virtual void ComputeJsonResult();

	void setResultState(ResultState newState);

	void onStartComputing();
	void onSucessfullyComputed();
	void onNotSucessComputing();

	bool ResultWasSucessfull();
};

template <typename TFutureResultInfo>
class IFutureResultImpl : public IFutureResult {
protected:
	TFutureResultInfo mFutureResultInfo;
public: 

	IFutureResultImpl();
};

template<typename TFutureResultInfo>
inline IFutureResultImpl<TFutureResultInfo>::IFutureResultImpl()
{
	mpFutureResultInfo = &mFutureResultInfo;
}
