﻿#pragma once

#include <BlueBlur.inl>

#include <Hedgehog/Base/Container/hhList.h>
#include <Hedgehog/Base/Container/hhMap.h>
#include <Hedgehog/Base/Type/hhSharedString.h>
#include <Hedgehog/Base/Thread/hhHolder.h>
#include <Hedgehog/Base/Thread/hhSynchronizedObject.h>
#include <Hedgehog/Base/hhObject.h>
#include <Hedgehog/Universe/Engine/hhUpdateManager.h>

namespace Hedgehog::Database
{
    class CDatabase;
}

namespace Sonic
{
    class CGameDocument;
    class CGameObject;
    class CLightManager;
    class CRenderDirector;
    class CWorld;

    static inline BB_FUNCTION_PTR(void, __stdcall, fpAddGameObject, 0xD631A0,
        CGameDocument* pGameDocument, const Hedgehog::Base::THolder<CWorld>& worldHolder,
        const boost::shared_ptr<CGameObject>& spGameObject, boost::shared_ptr<Hedgehog::Database::CDatabase>& spDatabase,
        CGameObject* pParentGameObject);

    class CGameDocument : public Hedgehog::Base::CSynchronizedObject
    {
    public:
        class CMember
        {
        public:
            boost::shared_ptr<Hedgehog::Universe::CUpdateManager> m_spUpdateManager;
            boost::shared_ptr<CRenderDirector> m_spRenderDirector;
            Hedgehog::map<Hedgehog::Base::CSharedString, boost::shared_ptr<CWorld>> m_Worlds;
            boost::shared_ptr<Hedgehog::Database::CDatabase> m_spDatabase;
            Hedgehog::list<boost::shared_ptr<CGameObject>> m_GameObjects;
            BB_INSERT_PADDING(0x18);
            Hedgehog::vector<size_t> m_PlayerIDs;
            BB_INSERT_PADDING(0x28);
            boost::shared_ptr<CLightManager> m_spLightManager;
            BB_INSERT_PADDING(0x128);
        };

        static constexpr CGameDocument** ms_pInstance = (CGameDocument**)0x1E0BE5C;

        static Hedgehog::Base::THolder<CGameDocument> GetInstance()
        {
            return *ms_pInstance;
        }

        CMember* m_pMember;
        BB_INSERT_PADDING(0x14);

        virtual ~CGameDocument() = default;

        Hedgehog::Base::THolder<CWorld> GetWorld(const char* name = "main") const
        {
            for (auto it = m_pMember->m_Worlds.begin(); it != m_pMember->m_Worlds.end(); it = it->next())
            {
                if (it->m_Value.m_Key == name)
                    return it->m_Value.m_Value.get();
            }

            return nullptr;
        }

        void AddGameObject(const boost::shared_ptr<CGameObject>& spGameObject, const char* worldName = "main", CGameObject* pParentGameObject = nullptr)
        {
            fpAddGameObject(this, GetWorld(worldName), spGameObject, m_pMember->m_spDatabase, pParentGameObject);
        }

        void AddUpdateUnit(const Hedgehog::Base::CSharedString& category, Hedgehog::Universe::CUpdateUnit* pUpdateUnit)
        {
            m_pMember->m_spUpdateManager->Add(category, pUpdateUnit);
        }
    };

    BB_ASSERT_OFFSETOF(CGameDocument::CMember, m_spUpdateManager, 0x0);
    BB_ASSERT_OFFSETOF(CGameDocument::CMember, m_spRenderDirector, 0x8);
    BB_ASSERT_OFFSETOF(CGameDocument::CMember, m_Worlds, 0x10);
    BB_ASSERT_OFFSETOF(CGameDocument::CMember, m_spDatabase, 0x1C);
    BB_ASSERT_OFFSETOF(CGameDocument::CMember, m_GameObjects, 0x24);
    BB_ASSERT_OFFSETOF(CGameDocument::CMember, m_PlayerIDs, 0x48);
    BB_ASSERT_OFFSETOF(CGameDocument::CMember, m_spLightManager, 0x80);
    BB_ASSERT_SIZEOF(CGameDocument::CMember, 0x1B0);

    BB_ASSERT_OFFSETOF(CGameDocument, m_pCriticalSection, 0x4);
    BB_ASSERT_OFFSETOF(CGameDocument, m_pMember, 0x8);
    BB_ASSERT_SIZEOF(CGameDocument, 0x20);
}