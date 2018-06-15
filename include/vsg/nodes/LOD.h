#pragma once

#include <vsg/core/ref_ptr.h>

#include <vsg/nodes/Node.h>

#include <array>
#include <algorithm>

namespace vsg
{
    struct Sphere
    {
        Sphere() : center{0.0,0.0,0.0}, radius(-1.0) {}

        bool valid() const { return radius>=0.0; }

        double    center[3];
        double    radius;
    };

    class LOD : public vsg::Node
    {
    public:
        LOD() {}

        virtual void accept(Visitor& visitor) { visitor.apply(*this); }

        // traverse all chukdren
        inline virtual void traverse(Visitor& visitor)
        {
            std::for_each(_children.begin(), _children.end(), [&visitor](ref_ptr<Node>& child)
            {
                if (child.valid()) child->accept(visitor);
            });
        }

        /// set the BondingSphere to use in culling/computation of which child is active.
        void setBoundingSohere(const Sphere& sphere) { _boundingSphere = sphere; }
        Sphere& getBoundingSohere() { return _boundingSphere; }
        const Sphere& getBoundingSohere() const { return _boundingSphere; }


        /// set the minimum screen space area that a child is visible from
        void setMinimumArea(std::size_t pos, double area) { _minimumAreas[pos] = area; }
        double getMinimumArea(std::size_t pos) const { return _minimumAreas[pos]; }

        void setChild(std::size_t pos, vsg::Node* node) { _children[pos] = node;}
        vsg::Node* getChild(std::size_t pos) { return _children[pos].get(); }
        const vsg::Node* getChild(std::size_t pos) const { return _children[pos].get(); }

        std::size_t getNumChildren() const { return 2; }

        using MinimumAreas = std::array< double, 2 > ;
        MinimumAreas& getMinimumAreas() { return _minimumAreas; }
        const MinimumAreas& getMinimumAreas() const { return _minimumAreas; }

        using Children = std::array< ref_ptr< vsg::Node>, 2 >;
        Children& getChildren() { return _children; }
        const Children& getChildren() const { return _children; }

    protected:

        virtual ~LOD() {}

        Sphere          _boundingSphere;
        MinimumAreas    _minimumAreas;
        Children        _children;
    };

}