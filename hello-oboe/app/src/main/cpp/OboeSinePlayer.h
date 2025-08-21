#ifndef HELLO_OBOE_OBOESINEPLAYER_H
#define HELLO_OBOE_OBOESINEPLAYER_H

#include <math.h>
#include <oboe/Oboe.h>

#include <algorithm>

/*
 * This class is responsible for creating an audio stream and starting it.
 * It specifies a callback function onAudioReady which is called each time
 * the audio stream needs more data.
 * Inside this callback either silence is rendered or if the isOn variable
 * is true a sine wave will be rendered.
 * The sine wave's frequency is hardcoded to 440Hz inside kFrequency.
 */
class OboeSinePlayer : public oboe::AudioStreamCallback {
 public:
  OboeSinePlayer() {
    oboe::AudioStreamBuilder builder;
    // The builder set methods can be chained for convenience.
    builder.setSharingMode(oboe::SharingMode::Exclusive);
    builder.setPerformanceMode(oboe::PerformanceMode::LowLatency);
    builder.setFormat(oboe::AudioFormat::Float);
    builder.setCallback(this);
    builder.openManagedStream(outStream);
    // Typically, start the stream after querying some stream information, as
    // well as some input from the user
    channelCount = outStream->getChannelCount();
    mPhaseIncrement = kFrequency * kTwoPi / outStream->getSampleRate();
    outStream->requestStart();
  }

  // This class will also be used for the callback
  // For more complicated callbacks create a separate class
  oboe::DataCallbackResult onAudioReady(oboe::AudioStream *oboeStream,
                                        void *audioData,
                                        int32_t numFrames) override {
    float *floatData = static_cast<float *>(audioData);
    if (isOn) {
      // Generate sine wave values
      for (int i = 0; i < numFrames; ++i) {
        float sampleValue = kAmplitude * sinf(mPhase);
        for (int j = 0; j < channelCount; j++) {
          floatData[i * channelCount + j] = sampleValue;
        }
        mPhase += mPhaseIncrement;
        if (mPhase >= kTwoPi) mPhase -= kTwoPi;
      }
    } else {
      // This will output silence
      std::fill_n(floatData, numFrames * channelCount, 0);
    }
    return oboe::DataCallbackResult::Continue;
  }

  void enable(bool toEnable) { isOn.store(toEnable); }

 private:
  // ManagedStream will release audio resources when destroyed.
  oboe::ManagedStream outStream;

  std::atomic_bool isOn{false};
  int channelCount;
  double mPhaseIncrement;

  // Wave params, these could be instance variables in order to modify at
  // runtime
  static float constexpr kAmplitude = 0.5f;
  static float constexpr kFrequency = 440;

  // Keeps track of where the wave is
  float mPhase = 0.0;

  static double constexpr kTwoPi = M_PI * 2;
};

#endif  // HELLO_OBOE_OBOESINEPLAYER_H
