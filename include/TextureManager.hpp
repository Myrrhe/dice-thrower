#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP


class TextureManager final
{
public:
    TextureManager() = delete;
    TextureManager(const TextureManager& right) = delete;
    TextureManager(TextureManager&& right) = delete;
    TextureManager& operator=(const TextureManager& right) = delete;
    TextureManager& operator=(TextureManager&& right) = delete;
    ~TextureManager() = delete;

    static void initialize();
    static void terminate();

protected:

private:
};

#endif // TEXTUREMANAGER_HPP
