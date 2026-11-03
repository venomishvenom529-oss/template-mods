#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

class $modify(MyEditorLayer, LevelEditorLayer) {
    // Хукаем стандартное обновление кадра редактора, чтобы проверять действия
    void update(float dt) {
        LevelEditorLayer::update(dt);
        
        // В будущем здесь можно привязать вызов к кнопке интерфейса
    }

    // Наша функция автодекорирования выделенных блоков
    void autoDecorateSelected() {
        auto* selectedObjects = m_editorLayer->m_selectedObjects;
        if (!selectedObjects || selectedObjects->count() == 0) {
            FLAlertLayer::create("Автодекор", "Сначала выделите объекты!", "OK")->show();
            return;
        }

        // Перебираем выделенные объекты
        CCObject* obj;
        CCARRAY_FOREACH(selectedObjects, obj) {
            auto* gameObject = typeinfo_cast<GameObject*>(obj);
            if (!gameObject) continue;

            CCPoint pos = gameObject->getPosition();

            // ID 44 — это классический белый внутренний квадрат декора
            int decorObjectID = 44; 
            auto* decor = m_editorLayer->createObject(decorObjectID, pos, false);

            if (decor) {
                // Ставим декор на слой выше основного блока
                decor->setZOrder(gameObject->getZOrder() + 1); 
                decor->setBaseColorID(1); // Назначаем 1-й цветовой канал
                m_editorLayer->addObject(decor);
            }
        }
        
        FLAlertLayer::create("Готово", "Базовый декор успешно наложен!", "Отлично")->show();
    }
};
