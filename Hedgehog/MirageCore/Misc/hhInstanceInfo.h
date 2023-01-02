#pragma once

#include <Hedgehog/MirageCore/MatrixNode/hhMatrixNodeListener.h>

namespace Hedgehog::Animation
{
    class CAnimationPose;
}

namespace Hedgehog::Mirage
{
    class CInstanceInfo : public CMatrixNodeListener
    {
    public:
        BB_INSERT_PADDING(0x24C);
        Math::CMatrix m_Transform;
        Math::CMatrix m_PrevTransform;
        BB_INSERT_PADDING(0x20);
        boost::shared_ptr<Animation::CAnimationPose> m_spAnimationPose;
        BB_INSERT_PADDING(0x48);
    };

    BB_ASSERT_OFFSETOF(CInstanceInfo, m_Transform, 0x250);
    BB_ASSERT_OFFSETOF(CInstanceInfo, m_PrevTransform, 0x290);
    BB_ASSERT_OFFSETOF(CInstanceInfo, m_spAnimationPose, 0x2F0);
    BB_ASSERT_SIZEOF(CInstanceInfo, 0x340);
}