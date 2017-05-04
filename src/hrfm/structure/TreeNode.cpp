#include "TreeNode.hpp"

namespace hrfm{ namespace structure{
    
    int TreeNode::numChildren(){
        return this->children.size();
    }
    
    bool TreeNode::hasChildOf( TreeNode * child ){
        auto itr = std::remove_if(this->children.begin(),this->children.end(),[child](TreeNode* d)->bool{
            return d == child;
        });
        if( itr == this->children.end() ){
            return false;
        }
        return true;
    }
    
    bool TreeNode::hasParent(){
        return this->_parent != nullptr && this->_parent != NULL;
    }
    TreeNode * TreeNode::getParent(){
        return this->_parent;
    }
    
    bool TreeNode::isRootNode(){
        return !this->hasParent();
    }
    TreeNode * TreeNode::getRootNode(){
        if( this->isRootNode() ){
            return this;
        }else{
            return this->getParent()->getRootNode();
        }
    }
    
    TreeNode * TreeNode::addChild( TreeNode * child ){
        this->eraseFromChildren(child);
        child->_setParent(this);
        this->children.push_back(child);
        return child;
    }
    
    TreeNode * TreeNode::addChildAt( TreeNode * child, int index ){
        if( this->numChildren() < index || index < 0 ){
            throw;
        }else if( this->numChildren() == index ){
            return this->addChild(child);
        }
        std::vector<TreeNode*>::iterator itr = this->children.begin() + index;
        if( *itr != child ){
            this->eraseFromChildren(child);
            this->children.insert(itr, child);
        }
        return child;
    }
    
    TreeNode * TreeNode::removeChild( TreeNode * child ){
        if( this->eraseFromChildren(child) ){
            child->_unsetParent();
        }
        return child;
    }
    
    TreeNode * TreeNode::removeChildAt( int index ){
        if( this->numChildren() <= index || index < 0 ){ throw; }
        std::vector<TreeNode*>::iterator itr = this->children.begin() + index;
        this->children.erase(itr);
        return *itr;
    }
    
    TreeNode * TreeNode::removeOwn(){
        if( this->hasParent() ){ this->getParent()->removeChild(this); }
        return this;
    }
    
    void TreeNode::update(){
        this->_update();
        this->_updateChildren();
    }
    
    void TreeNode::draw(){
        _draw();
        _drawChildren();
    }
    
    //! protected:
    
    inline bool TreeNode::eraseFromChildren( TreeNode * child ){
        auto itr = std::remove_if(children.begin(),children.end(),[child](TreeNode* d)->bool{
            return d == child;
        });
        if( itr == children.end() ){
            return false;
        }
        children.erase( itr, children.end() );
        return true;
    }
    
    void TreeNode::_update(){}
    void TreeNode::_updateChildren(){
        if( numChildren() == 0 ) return;
        std::vector<TreeNode*>::iterator it, end;
        for( it = children.begin(), end = children.end(); it!=end; it++ ){
            if( *it!=nullptr ){
                (*it)->update();
            }
        }
    }
    
    void TreeNode::_draw(){};
    void TreeNode::_drawChildren(){
        if( numChildren() == 0 ) return;
        std::vector<TreeNode*>::iterator it, end;
        for( it = children.begin(), end = children.end(); it!=end; it++ ){
            if( *it!=nullptr ){
                (*it)->draw();
            }
        }
    }
    
    void TreeNode::_setParent( TreeNode * node ){
        if( !hasParent() ){
            _parent = node;
            dispatchEvent( new hrfm::events::Event(hrfm::events::Event::ADDED) );
        }else{
            _parent = node;
        }
    }
    
    void TreeNode::_unsetParent(){
        if( hasParent() ){
            _parent = NULL;
            dispatchEvent( new hrfm::events::Event(hrfm::events::Event::REMOVED) );
        }
    }
    
}}