#pragma once

#include "EventDispatcher.h"

namespace hrfm{ namespace structure{
    
    class TreeNode : public hrfm::events::EventDispatcher{
    
    public:
        
        TreeNode():hrfm::events::EventDispatcher(){};
        ~TreeNode(){};
        
        std::vector<TreeNode*> children;
        
        virtual int  numChildren();
        
        virtual bool hasChildOf( TreeNode * child );
        
        virtual bool hasParent();
        virtual TreeNode * getParent();
        
        virtual bool isRootNode();
        virtual TreeNode * getRootNode();
        
        virtual TreeNode * addChild( TreeNode * child );
        virtual TreeNode * addChildAt( TreeNode * child, int index );
        
        virtual TreeNode * removeChild( TreeNode * child );
        virtual TreeNode * removeChildAt( int index );
        virtual TreeNode * removeOwn();
        
        virtual void update();
        virtual void draw();
        
    protected:
        
        // 更新処理.
        virtual void _update();
        virtual void _updateChildren();
        
        // 描画処理.
        virtual void _draw();
        virtual void _drawChildren();
        
        // Display Tree Control.
        
        //! 指定した要素を children から削除します. 削除された場合 true 存在しない場合は false を返します.
        bool eraseFromChildren( TreeNode * child );
        
        TreeNode * _parent = NULL;
        virtual void _setParent( TreeNode * node );
        virtual void _unsetParent();
        
    };
    
}}