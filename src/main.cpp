#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MegaChestMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        // Grab the bottom menu bar where the Geode button sits
        auto bottomMenu = this->getChildByID("bottom-menu");
        if (!bottomMenu) {
            return true;
        }

        // Create a giant "M" label using Geometry Dash's gold font
        auto mLabel = CCLabelBMFont::create("M", "goldFont.fnt");
        mLabel->setScale(1.35f);

        // Wrap the "M" inside a standard Geometry Dash circular button base
        auto btnSprite = CircleButtonSprite::create(
            mLabel,
            CircleBaseColor::Green,
            CircleBaseSize::MediumAlt
        );

        // Create the clickable button and bind it to our chest callback
        auto mButton = CCMenuItemSpriteExtra::create(
            btnSprite,
            this,
            menu_selector(MegaChestMenuLayer::onMegaChestClicked)
        );
        mButton->setID("mega-chest-button"_spr);

        // Add right next to the Geode button and refresh the menu layout
        bottomMenu->addChild(mButton);
        bottomMenu->updateLayout();

        return true;
    }

    void onMegaChestClicked(CCObject* sender) {
        // Build the list of reward objects inside the chest
        auto rewards = CCArray::create();

        // SpecialRewardItem values in GD:
        // Orbs = 7, Diamonds = 8, Demon Keys = 6, Gold Keys = 12
        rewards->addObject(GJRewardObject::create(SpecialRewardItem::Orbs, 999999, 0));
        rewards->addObject(GJRewardObject::create(SpecialRewardItem::Diamonds, 999999, 0));
        rewards->addObject(GJRewardObject::create(SpecialRewardItem::DemonKey, 999999, 0));
        rewards->addObject(GJRewardObject::create(static_cast<SpecialRewardItem>(12), 30, 0));

        // Wrap the rewards in a GJRewardItem (Large Treasure Chest)
        auto rewardItem = GJRewardItem::createWithObjects(GJRewardType::LargeTreasure, rewards);

        // Open the native chest unlock layer (type 2 = Large Treasure Chest)
        auto unlockLayer = RewardUnlockLayer::create(2, nullptr);
        unlockLayer->m_chestType = 2;
        unlockLayer->showCollectReward(rewardItem);

        // Display the chest popup on the current scene
        CCDirector::get()->getRunningScene()->addChild(unlockLayer, 100);
    }
};
