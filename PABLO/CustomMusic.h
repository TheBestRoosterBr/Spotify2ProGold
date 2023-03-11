#ifndef CUSTOMMUSIC_H_INCLUDED
#define CUSTOMMUSIC_H_INCLUDED

#include <SFML/Audio.hpp>
#include <mpg123.h>

class CustomMusic : public sf::SoundStream
{
public:
    CustomMusic() : m_mh(nullptr), m_duration(sf::Time::Zero) {}

    bool open(const std::string& filename)
    {
        // Inicializa a biblioteca libmpg123
        if (mpg123_init() != MPG123_OK)
        {
            return false;
        }

        // Cria uma instância do mpg123_handle
        m_mh = mpg123_new(NULL, NULL);
        if (m_mh == nullptr)
        {
            return false;
        }

        // Abre o arquivo MP3 com a biblioteca libmpg123
        if (mpg123_open(m_mh, filename.c_str()) != MPG123_OK)
        {
            return false;
        }

        // Obtém as informações do arquivo MP3
        long rate;
        int channels, encoding;
        mpg123_getformat(m_mh, &rate, &channels, &encoding);
        double length = mpg123_length(m_mh) / (double)rate;

        // Define a taxa de amostragem e o número de canais da música
        initialize(channels, rate);

        // Cria um buffer para armazenar os dados decodificados do arquivo MP3
        m_buffer.resize(mpg123_outblock(m_mh));

        // Calcula a duração da música
        size_t totalSamples = static_cast<size_t>(length * getSampleRate() * getChannelCount());
        m_duration = sf::seconds(static_cast<float>(totalSamples) / static_cast<float>(getSampleRate()) / static_cast<float>(getChannelCount()));

        return true;
    }

    void close()
    {
        // Libera os recursos
        stop();
        if (m_mh != nullptr)
        {
            mpg123_close(m_mh);
            mpg123_delete(m_mh);
            mpg123_exit();
            m_mh = nullptr;
        }
    }

    sf::Time getDuration() const
    {
        return m_duration;
    }


    int getCurrentTime() const
    {
        // Obtém a posição atual em bytes
        off_t currentByte = mpg123_tell(m_mh);

        // Obtém informações sobre a posição atual em amostras e a taxa de quadros atual
        mpg123_frameinfo info;
        mpg123_info(m_mh, &info);

        // Calcula a posição atual em segundos
        return sf::seconds(static_cast<float>(currentByte) / static_cast<float>(info.framesize) * static_cast<float>(info.framesize) / static_cast<float>(getSampleRate()) / static_cast<float>(getChannelCount())).asSeconds() * 2;
    }



private:
    virtual bool onGetData(Chunk& data)
    {
        size_t done = 0;
        if (mpg123_read(m_mh, reinterpret_cast<unsigned char*>(&m_buffer[0]), m_buffer.size(), &done) == MPG123_OK)
        {
            data.samples = reinterpret_cast<const sf::Int16*>(&m_buffer[0]);
            data.sampleCount = static_cast<std::size_t>(done) / sizeof(sf::Int16);
        }
        else
        {
            data.samples = nullptr;
            data.sampleCount = 0;
        }

        return true;
    }

    virtual void onSeek(sf::Time timeOffset)
    {
        mpg123_seek(m_mh, static_cast<off_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount()), SEEK_SET);
    }

    mpg123_handle* m_mh;
    std::vector<sf::Int16> m_buffer;
    sf::Time m_duration;
};

#endif // CUSTOMMUSIC_H_INCLUDED
