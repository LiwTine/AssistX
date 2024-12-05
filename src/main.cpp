#include "recognizer/RecognizeVosk.h"
#include "voice/InputVoice.h"

int main() {

    RecognizeVosk recognize;

    recognize.initialize();

    recognize.executeProcessing();

    InputVoice voice;

    voice.initialize();

    voice.executeProcessing();

    return 0;
}
