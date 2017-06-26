#include <iostream>
#include <map>

#include <zaudio/sdl/audiosamplesdl.h>
#include <zaudio/sdl/audioloadersdl.h>
#include <zaudio/sdl/audiosamplersdl.h>

#include "bluetooth.h"

int main(int argc, const char *argv[])
{
    Bluetooth bt;

    if(!bt.connect("/dev/rfcomm0"))
    {
        std::cerr << "Fail" << std::endl;
        return -1;
    }

    AudioSamplerSDL sampler;
    std::map<std::string, std::shared_ptr<IAudioSample>> m_samples;
    m_samples["c1"] = AudioLoaderSDL::loadWav("res/samples/c1.wav");
    m_samples["d1"] = AudioLoaderSDL::loadWav("res/samples/d1.wav");
    m_samples["e1"] = AudioLoaderSDL::loadWav("res/samples/e1.wav");
    m_samples["f1"] = AudioLoaderSDL::loadWav("res/samples/f1.wav");
    m_samples["g1"] = AudioLoaderSDL::loadWav("res/samples/g1.wav");
    m_samples["a1"] = AudioLoaderSDL::loadWav("res/samples/a1.wav");
    m_samples["h1"] = AudioLoaderSDL::loadWav("res/samples/h1.wav");
    m_samples["c2"] = AudioLoaderSDL::loadWav("res/samples/c2.wav");

    std::string lastData;
    sampler.setOnAllSamplesEndListener([&](void) {
            lastData = "";
        });

    while(1)
    {
        std::string data;
        data = bt.readLine();

        std::cout << "Last data: " << lastData << std::endl
                  << "Data:      " << data << std::endl
                  << "-------------------------------" << std::endl;

        if(data != lastData)
        {
            auto sample = m_samples.at(data);
            sampler.play(sample);
            lastData = data;
        }
    }

    return 0;
}
