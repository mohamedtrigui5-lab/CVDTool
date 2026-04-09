#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <optional>
#include <filesystem>
#include <windows.h>
#include "ImageHandler.h"
#include "Encoder.h"
#include "FileCVD.h"
#include "ZoomHandler.h"

namespace fs = std::filesystem;

// 1. Détection de la langue système
bool isFrench() { return GetUserDefaultUILanguage() == 0x040c; }

// 2. Boîte de dialogue Windows native
std::string openFileDialog(bool isCVD) {
    char filename[MAX_PATH] = { 0 };
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    // Filtre pour accepter .cvd, .cvd1 et .cvd2
    ofn.lpstrFilter = isCVD ? "CVD Files\0*.cvd*\0" : "Images\0*.png;*.jpg;*.jpeg;*.bmp\0";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    if (GetOpenFileNameA(&ofn)) return std::string(filename);
    return "";
}

int main()
{
    // Singleton : Empêche d'ouvrir l'outil deux fois
    HANDLE hMutex = CreateMutexA(NULL, TRUE, "CVD_TOOL_SINGLETON");
    if (GetLastError() == ERROR_ALREADY_EXISTS) return 0;

    sf::RenderWindow window(sf::VideoMode({ 1024, 768 }), "CVD Tool");
    bool french = isFrench();

    sf::Image originalImg, displayImg;
    sf::Texture tex;
    sf::Sprite sprite(tex);
    float currentZoom = 1.0f;
    std::string currentFileName = (french ? "Aucun" : "None");


    // --- FONCTION : MISE À JOUR DE L'AFFICHAGE ---
    auto updateDisplay = [&]() {
        if (displayImg.getSize().x == 0) return;
        (void)tex.loadFromImage(displayImg);
        tex.setSmooth(true);
        sprite.setTexture(tex, true);

        // Calcul du ratio pour l'ajustement à la fenêtre
        float scaleX = 1024.f / (float)displayImg.getSize().x;
        float scaleY = 768.f / (float)displayImg.getSize().y;
        float scale = std::min(1.0f, std::min(scaleX, scaleY));

        sprite.setScale({ scale * currentZoom, scale * currentZoom });

        // Centrage du sprite
        float offsetX = (1024.f - (displayImg.getSize().x * scale * currentZoom)) / 2.f;
        float offsetY = (768.f - (displayImg.getSize().y * scale * currentZoom)) / 2.f;
        sprite.setPosition({ offsetX, offsetY });

        window.setView(window.getDefaultView());
        };

    // --- FONCTION : MISE À JOUR DU TITRE (INSTRUCTIONS) ---
    auto updateUI = [&](std::string status = "") {
        std::string title = status;
        if (title.empty()) {
            if (french) {
                title = currentFileName + " | O: Image (CVD1) | P: Compresse (CVD2) | L: Charger | Z/X: Zoom";
            }
            else {
                title = currentFileName + " | O: Image (CVD1) | P: Compress (CVD2) | L: Load | Z/X: Zoom";
            }
        }
        window.setTitle(title);
        };

    // --- FONCTION : ENCODER ET SAUVEGARDER ---
    auto encodeAndSave = [&](const std::string& path, int quality) {
        std::string ext = (quality == 0) ? ".cvd1" : ".cvd2";
        updateUI(french ? "Traitement en cours..." : "Processing...");

        sf::Image img = ImageHandler::loadImage(path);
        if (img.getSize().x > 0) {
            originalImg = img;
            displayImg = originalImg;
            currentZoom = 1.0f;
            currentFileName = fs::path(path).stem().string();

            auto encoded = Encoder::encode(originalImg, quality);
            FileCVD::save(currentFileName + ext, encoded, img.getSize().x, img.getSize().y);

            updateDisplay();
            updateUI(currentFileName + ext + (french ? " cree !" : " created !"));
            // On laisse le message de succès 2 secondes, puis les instructions reviennent via le pollEvent
        }
        };

    // --- FONCTION : CHARGER UN CVD ---
    auto loadCVDFile = [&](const std::string& path) {
        updateUI(french ? "Decodage en cours..." : "Decoding...");
        int w, h;
        auto decodedData = FileCVD::load(path, w, h);

        if (!decodedData.empty()) {
            originalImg = Encoder::decode(decodedData, (unsigned int)w, (unsigned int)h);
            displayImg = originalImg;
            currentZoom = 1.0f;
            currentFileName = fs::path(path).stem().string();
            updateDisplay();
            updateUI();
        }
        };

    // --- INITIALISATION AU DÉMARRAGE ---
    if (fs::exists("input.png")) {
        encodeAndSave("input.png", 0);
    }

    // FORCE LE TITRE AVEC LES INSTRUCTIONS (au lieu du message de succès)
    currentFileName = fs::exists("input.png") ? "input" : (french ? "Aucun" : "None");
    updateUI();


    // --- BOUCLE PRINCIPALE ---
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {

                // O : LOSSLESS (CVD1)
                if (key->code == sf::Keyboard::Key::O) {
                    std::string path = openFileDialog(false);
                    if (!path.empty()) encodeAndSave(path, 0);
                }

                // P : LOSSY (CVD2)
                else if (key->code == sf::Keyboard::Key::P) {
                    std::string path = openFileDialog(false);
                    if (!path.empty()) encodeAndSave(path, 15);
                }

                // L : CHARGER
                else if (key->code == sf::Keyboard::Key::L) {
                    std::string path = openFileDialog(true);
                    if (!path.empty()) loadCVDFile(path);
                }

                // ZOOM Z / X
                else if (key->code == sf::Keyboard::Key::Z) {
                    currentZoom *= 1.1f;
                    updateDisplay();
                }
                else if (key->code == sf::Keyboard::Key::X) {
                    currentZoom /= 1.1f;
                    if (currentZoom < 0.1f) currentZoom = 0.1f;
                    updateDisplay();
                }

                // Reset instructions si un message temporaire était affiché
                updateUI();
            }
        }

        window.clear(sf::Color(25, 25, 25));
        if (displayImg.getSize().x > 0) {
            window.draw(sprite);
        }
        window.display();
    }

    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
    return 0;
}
