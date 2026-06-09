#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCScheduler.hpp>

using namespace geode::prelude;

// Variabel Global buat simpan status cheat (True = Aktif, False = Mati)
bool g_noclip = false;
float g_speed = 1.0f;

// ==================== 1. FITUR NOCLIP ====================
class $modify(MyPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        // Kalau noclip aktif, block fungsi hancur/mati
        if (g_noclip) {
            return;
        }
        // Kalau gak aktif, jalankan fungsi mati normal bawaan game
        PlayLayer::destroyPlayer(player, object);
    }
};

// ==================== 2. FITUR SPEEDHACK ====================
class $modify(CCScheduler) {
    void update(float dt) {
        // Modifikasi delta time game pake variabel speed kita
        CCScheduler::update(dt * g_speed);
    }
};

// ==================== 3. MENU TOGGLE (Contoh Pemicu) ====================
// Nanti lu bisa kembangin ini jadi GUI/Menu Pop-up keren.
// Sementara, kita bikin cheat-nya otomatis aktif pas game dimainin buat ngetes.
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Otomatis aktifin noclip & set speed pas masuk main menu buat testing build
        g_noclip = true; 
        g_speed = 1.5f; // Game jadi 1.5x lebih cepet

        return true;
    }
};
