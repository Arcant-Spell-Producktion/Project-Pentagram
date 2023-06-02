#include "CreditSlide.h"

#include "Game/BattleScene/GameObject/CasterObject.h"
#include "Game/Objects/StageObject.h"

void CreditSlide::QueueMoveEvent(std::vector<int> imageIds, glm::vec3 startPos, glm::vec3 endPos, float travelTime)
{
    glm::vec3 direction = endPos - startPos;

    QueueUpdateFunction(
        [this, imageIds,startPos, direction, travelTime](float dt)
        {
            if (m_TotalTime >= travelTime)
            {
                Next();
                return;
            }

            float progress = m_TotalTime / travelTime;

            for (int image : imageIds)
            {
                m_Images[image]->position.x = startPos.x + direction.x * progress;
                m_Images[image]->position.y = startPos.y + direction.y * progress;
            }
        }
    );
}

void CreditSlide::QueueWaitTillFrameEvent(int id,bool doNextRow, bool waitLastFrame, int targetFrame)

{
    QueueUpdateFunction(
        [this,id, doNextRow, waitLastFrame, targetFrame](float dt)
        {
            m_Images[id]->SetActive(true);
            int _target = targetFrame;
            int currentRow = m_Images[id]->GetCurrentAnimationRow() - 1;
            int lastFrame = m_Images[id]->GetAnimationColumn(currentRow);

            if (waitLastFrame || _target == -1) _target = lastFrame;

            int curFrame = m_Images[id]->GetCurrentAnimationColumn();
            if (curFrame == _target)
            {
                if (doNextRow) m_Images[id]->SetSpriteByIndex(currentRow + 1, 0, true);

                Next();
                return;
            }
        }
    );
}

SlideObject* CreditSlide::Init()
{

    const std::string creditA = "Producer\n\nPada Cherdchoothai\n\nDirector\n\nChakra Withitkun";
    const std::string creditB = "Programmer\n\nPada Cherdchoothai\nSiravich Sereepong";
    const std::string creditC = "Game Designer\n\nChakra Withitkun\nPawin Techatanates\n\nSound Designer\n\nAkenat Lertbuaban";
    const std::string creditD = "Artist\n\nMamay Euaareepichit\nPraewa Ekphech";
    const std::string creditE = "Project Adviser\n\nASST.Prof.Dr.Pisal Setthawong\nAjarn Pakpoom Thongsari\n TA Nonthi Sithikong\nTA Worawit Peerapolchaikul";

#pragma region Init

    // Game Logo
    GameObject* gameLogo = new GameObject("GameLogo");
    gameLogo->SetTexture("Sprites/Logo/logo_game.png");
    gameLogo->scale = { 1000.0f, 708.0f, 1.0f };
    gameLogo->position = { 0.0f, 0.0f, 0.0f };

    // Team Logo
    GameObject* teamLogo = new GameObject("TeamLogo");
    teamLogo->SetTexture("Sprites/Logo/logo_arcant.png");
    teamLogo->scale = { 600.0f, 600.0f, 1.0f };
    teamLogo->position = { 0.0f, 0.0f, 0.0f };

    // KMUTT Logo
    GameObject* KMUTTLogo = new GameObject("KMUTTLogo");
    KMUTTLogo->SetTexture("Sprites/Logo/logo_kmutt.png");
    KMUTTLogo->scale = { 500.0f, 500.0f, 1.0f };
    KMUTTLogo->position = { -550.0f, 0.0f, 0.0f };

    // DDCT Logo
    GameObject* DDCTLogo = new GameObject("DDCTLogo");
    DDCTLogo->SetTexture("Sprites/Logo/logo_ddct.png");
    DDCTLogo->scale = { 1000.0f, 375.0f, 1.0f };
    DDCTLogo->position = { 310.0f, -140.0f, 0.0f };

    //Spells
    GameObject* Fireball = new GameObject("Fireball");
    Fireball->SetTexture("Sprites/Spell/Fire/spell_fire_1.png");
    Fireball->SetIsAnimationObject(true);
    Fireball->scale = { 4500.0f, 4500.0f, 1.0f };
    Fireball->position.x = -3500.0f;

    GameObject* Waterbeam = new GameObject("Waterbeam");
    Waterbeam->SetTexture("Sprites/Spell/Water/spell_water_9-1.png");
    Waterbeam->SetSpriteByIndex(1, 0);
    Waterbeam->SetAnimationPlayTime(0.15f);
    Waterbeam->SetIsAnimationObject(true);
    Waterbeam->scale = { -6000.0f, 2000.0f, 1.0f };
    

    GameObject* Tornado = new GameObject("Tornado");
    Tornado->SetTexture("Sprites/Spell/Wind/spell_sprite_wind4.png");
    Tornado->SetSpriteByIndex(2, 0);
    Tornado->SetAnimationPlayTime(0.15f);
    Tornado->SetIsAnimationObject(true);
    Tornado->scale = { 4500.0f, 4500.0f, 1.0f };
    Tornado->position.x = -3500.0f;

    GameObject* EarthPrison = new GameObject("EarthPrison");
    EarthPrison->SetTexture("Sprites/Spell/Earth/spell_earth_6.png");
    EarthPrison->SetAnimationPlayTime(0.15f);
    EarthPrison->SetIsAnimationObject(true);
    EarthPrison->scale = { 6000.0f, 3000.0f, 1.0f };
    EarthPrison->position.y = -500.0f;

    //Stage
    StageObject* Stage = new StageObject(Element::Fire);

    CasterObject* CasterA = new CasterObject();
    CasterA->SetCaster(CasterType::Player, Element::Fire,CasterPosition::CasterA);

    CasterObject* CasterB = new CasterObject();
    CasterB->SetCaster(CasterType::Player, Element::Water, CasterPosition::CasterB);

    CasterObject* CasterEX1 = new CasterObject();
    CasterEX1->SetCaster(CasterType::Player, Element::Wind, CasterPosition::CasterA);
    CasterEX1->position = { -CASTER_POSITION_X - 125.0f, CASTER_POSITION_Y + 20.0f, 1.0f };

    CasterObject* CasterEX2 = new CasterObject();
    CasterEX2->SetCaster(CasterType::Player, Element::Water, CasterPosition::CasterA);
    CasterEX2->position = { -CASTER_POSITION_X + 25.0f, CASTER_POSITION_Y - 20.0f, 1.0f };


    CasterObject* CasterEX3 = new CasterObject();
    CasterEX3->SetCaster(CasterType::Player, Element::Earth, CasterPosition::CasterA);
    CasterEX3->position = { -CASTER_POSITION_X - 275.0f, CASTER_POSITION_Y - 20.0f, 1.0f };

    TextObject* TopText = new TextObject("TopText");
    TopText->text = "TOP TEXT";
    TopText->fontSize = 64;
    TopText->textAlignment = TextAlignment::MID;
    TopText->isVCenterAlignment = true;
    TopText->position = { 0.0f, 450.0f, 0.0f };

    TopText->text = "Presented by";
    
    TextObject* BottomText = new TextObject("BottomText");
    BottomText->text = "Bottom TEXT";
    BottomText->fontSize = 96;
    BottomText->textAlignment = TextAlignment::MID;
    BottomText->isVCenterAlignment = true;
    BottomText->position = { 0.0f, -410.0f, 0.0f };

    BottomText->text = "Arcant Spell Production";

    TextObject* CenterText = new TextObject("CenterText");
    CenterText->text = creditA;
    CenterText->fontSize = 64;
    CenterText->textAlignment = TextAlignment::MID;
    CenterText->isVCenterAlignment = true;
    CenterText->outlineColor = AC_BLACK;
    CenterText->lineSpacing = 1.75f;


#pragma endregion

    int _gameLogo = AddImageObject(gameLogo);
    int _teamLogo = AddImageObject(teamLogo);
    int _kmuttLogo = AddImageObject(KMUTTLogo);
    int _ddctLogo = AddImageObject(DDCTLogo);

    int _stage = AddImageObject(Stage);
    int _casterA = AddImageObject(CasterA);
    int _casterB = AddImageObject(CasterB);

    int _casterEX3 = AddImageObject(CasterEX3);
    int _casterEX1 = AddImageObject(CasterEX1);
    int _casterEX2 = AddImageObject(CasterEX2);

    int _fireBall = AddImageObject(Fireball);
    int _waterBeam = AddImageObject(Waterbeam);
    int _tornado = AddImageObject(Tornado);
    int _earthPrison = AddImageObject(EarthPrison);

    int _topText = AddTextObject(TopText);
    int _bottomText = AddTextObject(BottomText);
    int _centerText = AddTextObject(CenterText);

    TopText->SetRenderTime(0.01f);
    BottomText->SetRenderTime(0.01f);
    CenterText->SetRenderTime(0.05f);

    QueueWaitEvent(1);
    QueueFadeFromBlackEvent({ _gameLogo });
    QueueWaitEvent(2);
    QueueFadeToBlackEvent();
    QueueTextEvent({ _topText });
    QueueWaitEvent(1);
    QueueFadeInEvent({ _teamLogo },1);
    QueueTextEvent({ _bottomText });
    QueueUpdateFunction(
        [this, teamLogo, Fireball](float dt)
        {
            float progress = m_TotalTime / 1.0f;
            teamLogo->rotation = progress * 360.0f;

            if (m_TotalTime >= 1.0f)
            {
                Fireball->SetActive(true);
                Next();
                return;
            }

        }
    );
    QueueWaitEvent(1);
    QueueUpdateFunction(
        [this, _topText, _bottomText](float dt)
        {
            HideText(_topText);
            HideText(_bottomText);
            Next();
        }
    );
    QueueMoveEvent({ _fireBall }, { -3500.0f, 0, 1.0f }, { -500.0f, 0, 1.0f }, 2.0f);
    QueueFadeInEvent({ _stage,_casterA,_casterB }, 1, 0.5f);
    QueueMoveEvent({ _fireBall }, { -500.0f, 0, 1.0f }, { 3500.0f, 0, 1.0f }, 2.0f);
    QueueUpdateFunction(
        [this, Fireball](float dt)
        {
            Fireball->SetActive(false);
            Next();
        }
    );

    QueueTextEvent({ _centerText });
    QueueWaitEvent(4);
    QueueUpdateFunction(
        [this, _centerText, creditB,Waterbeam](float dt)
        {
            HideText(_centerText);
            m_Texts[_centerText]->text = creditB;
            Waterbeam->SetActive(true);
            Next();
        }
    );

    QueueWaitTillFrameEvent(_waterBeam, true);
    QueueWaitEvent(2);
    QueueUpdateFunction(
        [this, Stage, CasterA, CasterB](float dt)
        {
            Stage->SetElement(Element::Water);
            CasterA->SetCaster(CasterType::Player, Element::Wind);
            Next();
        }
    );
    QueueFadeOutEvent({ _waterBeam });

    QueueUpdateFunction(
        [this, _centerText](float dt)
        {
            m_Texts[_centerText]->SetRenderTime(0.05f);
            ShowText(_centerText);
            Next();
        }
    );
    QueueWaitEvent(4);
    QueueUpdateFunction(
        [this, _centerText, creditC, Tornado](float dt)
        {
            HideText(_centerText);
            m_Texts[_centerText]->text = creditC;
            Tornado->SetActive(true);

            Next();
        }
    );

    QueueMoveEvent({ _tornado }, { -3500.0f, 0, 1.0f }, { -500.0f, 0, 1.0f }, 2.0f);
    QueueUpdateFunction(
        [this, Stage, CasterA, CasterB](float dt)
        {
            Stage->SetElement(Element::Wind);
            CasterB->SetCaster(CasterType::Player, Element::Earth);
            Next();
        }
    );
    QueueMoveEvent({ _tornado }, { -500.0f, 0, 1.0f }, { 3500.0f, 0, 1.0f }, 2.0f);
    QueueUpdateFunction(
        [this, Tornado](float dt)
        {
            Tornado->SetActive(false);
            Next();
        }
    );


    QueueUpdateFunction(
        [this, _centerText](float dt)
        {
            m_Texts[_centerText]->SetRenderTime(0.05f);
            ShowText(_centerText);
            Next();
        }
    );
    QueueWaitEvent(7);
    QueueUpdateFunction(
        [this, _centerText, creditD,EarthPrison](float dt)
        {
            HideText(_centerText);
            m_Texts[_centerText]->text = creditD;
            EarthPrison->SetActive(true);
            Next();
        }
    );

    QueueWaitTillFrameEvent(_earthPrison, false, false, 5);
    QueueUpdateFunction(
        [this,EarthPrison](float dt)
        {
            EarthPrison->SetIsAnimationObject(false);
            Next();
        }
    );
    QueueUpdateFunction(
        [this, Stage, CasterA, CasterB](float dt)
        {
            Stage->SetElement(Element::Earth);
            CasterA->SetCaster(CasterType::Player, Element::Fire);
            Next();
        }
    );
    QueueWaitEvent(1);
    QueueUpdateFunction(
        [this, EarthPrison](float dt)
        {
            EarthPrison->SetIsAnimationObject(true);
            Next();
        }
    );
    QueueWaitTillFrameEvent(_earthPrison, false, true);
    QueueUpdateFunction(
        [this, EarthPrison](float dt)
        {
            EarthPrison->SetActive(false);
            Next();
        }
    );
    QueueUpdateFunction(
        [this, _centerText](float dt)
        {
            m_Texts[_centerText]->SetRenderTime(0.05f);
            ShowText(_centerText);
            Next();
        }
    );
    QueueWaitEvent(4);
    QueueFadeToBlackEvent(2);
    QueueUpdateFunction(
        [this, Stage, CasterA, CasterB](float dt)
        {
            Stage->SetElement(Element::Corrupt);
            CasterA->SetCaster(CasterType::Player, Element::Fire);
            CasterB->SetCaster(CasterType::BigBoss, Element::Fire);
            CasterA->position = { -CASTER_POSITION_X + 175.0f, CASTER_POSITION_Y + 20.0f, 1.0f };
            Next();
        }
    );

    QueueFadeFromBlackEvent({ _stage,_casterA,_casterB,_casterEX1,_casterEX2,_casterEX3 });
    QueueUpdateFunction(
        [this, _centerText , creditE , BottomText](float dt)
        {
            BottomText->fontSize = 28;
            BottomText->text = "(C)2023 DIGITAL DESIGN AND CREATIVE TECHNOLOGY";
            BottomText->SetRenderTime(0.05f);

            m_Texts[_centerText]->text = creditE;
            m_Texts[_centerText]->SetRenderTime(0.05f);
            ShowText(_centerText);
            Next();
        }
    );
    QueueWaitEvent(8);
    QueueFadeToBlackEvent();


    QueueFadeFromBlackEvent({ _kmuttLogo, _ddctLogo });
    QueueTextEvent({  _bottomText });
    QueueWaitEvent(3);
    QueueFadeToBlackEvent();

    return this;
}
