#ifndef VRB_FILE_READER_ANDROID_DOT_H
#define VRB_FILE_READER_ANDROID_DOT_H

#include "vrb/FileReader.h"
#include "vrb/Forward.h"

#include <jni.h>
#include <memory>

namespace vrb {

class FileReaderAndroid : public FileReader {
public:
  static FileReaderAndroidPtr Create();
  void ReadRawFile(const std::string& aFileName, FileHandlerPtr aHandler) override;
  void ReadImageFile(const std::string& aFileName, FileHandlerPtr aHandler) override;
  void SetAssetManager(JNIEnv* aEnv, jobject& aAssetManager);
  void ClearAssetManager();
  void ProcessImageFile(const int aFileHandle, std::unique_ptr<uint8_t[]>& aImage, const int aWidth, const int aHeight);
  void ImageFileLoadFailed(const int aFileHandle, const std::string& aReason);
protected:
  FileReaderAndroid();
  ~FileReaderAndroid();

  struct State;
  State* m;

private:
  FileReaderAndroid(const FileReaderAndroid&) = delete;
  FileReaderAndroid& operator=(const FileReaderAndroid&) = delete;
};

} // namespace vrb


#endif // VRB_FILE_READER_ANDROID_DOT_H