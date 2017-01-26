/*
 * Given a key value k, find value
 * NOTE: none of the below functions are build-ready. They cannot be
 * 	 run and is only for the purpose of demonstrating the algorithm
 */

Node findVal(k,currentnode){
    if (currentnode.key==k){
        return currentnode; //We have found the value
    }
    else if (currentnode.key<k){
        value = finalVal(k,currentnode.right);
        //If the value is bigger than current node, traverse to right branch
        return value;
    }
    else{
        value = finalVal(k,currentnode.left);
        return value;
    }
}

/*
 * Given an with key k, priority p, insert into tree A
 * Because the problem did not specify handling of this tree, I will
 * assume the BST is implemented using a linked-list and I will write an
 * algorithm that is suitable for a linked-list.
 * Rotations are not required because if insertion occurs between two nodes,
 * algorithm will create a new level thus maintaining priority.
 */

Node insertKey(k,p,currentnode,parentNode){//Function returns newroot if newroot 
                                  //created,else returns NULL.
    if(currentnode.priority<p&&parentNode==NULL){
                    //If this current node has lower priority and this is the
                    //rootnode, create new root with this item.
        Node newroot = new Node;
        Node.key = k;
        Node.priority = p;
        if(k<currentnode.key){
            Node.right=currentnode;
        }
        else
            Node.left=currentnode;
        return newroot;
        //Create new rootNode, link it to currentnode.
    }
    if(currentnode.priority>p){//Priority lower, keep traversing
        if(currentnode.key>k){//If k is smaller than current key, go left
            if(currentnode.left==NULL){//If already bottom of the tree with empty node,
                currentnode.left = new Node;
                currentnode.left->key=k;   //insert here.
                currentnode.left->priority=p;
                return NULL;
            }
            //If not bottom of the tree, i.e. not returned, traverse down
            insertKey(k,p,currentnode.left,currentnode);//passes itself as parent node
            return NULL;
        }
        else {//Go right
            if(currentnode.right==NULL){//If already bottom of the tree with empty node,
                currentnode.right = new Node;
                currentnode.right->key=k;   //insert here.
                currentnode.right->priority=p;
                return NULL;
            }
            //If not bottom of the tree, i.e. not returned, traverse down
            insertKey(k,p,currentnode.right,currentnode);//passes itself as parent node
            return NULL;
        }
    }
    else{//Insert here and this is not root.
        Node newnode = new Node;
        newnode.key = k;
        newnode.priority = p;
        //Relink new node to parent node
        if(k<parentNode.key)
            parentNode.left=newnode;
        else
            parentNode.right=newnode;
        
        //Relink new node to child node
        if(k<currentnode.key)
            newnode.right=currentnode;
        else
            newnode.left=currentnode;
        
        
        return NULL;
    }
}

/*
 * Given a value k, delete that item from tree. Returns rootnode if new rootnode
 * else returns NULL.
 */

Node deleteKey(k,currentnode, parentnode){
    if (currentnode.key>k){
        return deleteKey(k,currentnode.left, currentnode);
    }
    else if (currentnode.key<k){
        return deleteKey(k,currentnode.right, currentnode);
    }
    else{//We have found the node to delete
        if(currentnode.left==NULL&&currentnode.right==NULL){
            //If both childs are NULL, just delete
            if(parentnode==NULL){
                //If this is the only node
                delete currentnode;
                return NULL;
            }
            else{
                //Else delete currentnode and set pointer from parent to NULL.
                delete currentnode;
                if(parentnode.key>k)
                    parentnode.left=NULL;
                else
                    parentnode.right=NULL;
                
                return NULL;
            }
        }
        else if(currentnode.left==NULL||curretnode.right==NULL){
            //If only one child, let that child be this node.
            //Relink parent and child nodes
            if(currentnode.left!=NULL){
                if(parentnode.key>k)
                    parentnode.left=curretnode.left;
                else
                    parentnode.right=currentnode.left
            }
            else{
                if(parentnode.key>k)
                    parentnode.left=curretnode.right;
                else
                    parentnode.right=currentnode.right
            }
            delete currentnode;
            return NULL;
        }
        else{
            //If two children, rotate node to be deleted to the direction of
            //higher priority until only 1 child or no children remain
            if(currentnode.left->p>currentnode.right->p){
                //If left has higher priority than right, go left
                if(parentnode.key>k)
                    parentnode.left=curretnode.left;
                else
                    parentnode.right=currentnode.left;
                
                //relink nodes
                Node* tempNode;
                tempNode = currentnode.left; //let tempnode temporarily hold
                //pointer to rotated node
                currentnode.left=currentnode.left->right;
                //Finishing rotating onto node to be deleted.
                
                tempNode->right=currentnode;
                //put node to be deleted as right node of rotated node
                deleteKey(k,currentnode,tempnode)
            }
            
            else{
                //Rotate to the right
                if(parentnode.key>k)
                    parentnode.left=curretnode.right;
                else
                    parentnode.right=currentnode.right;
                
                //relink nodes
                Node* tempNode;
                tempNode = currentnode.right; //let tempnode temporarily hold
                //pointer to rotated node
                currentnode.right=currentnode.right->left;
                //Finishing rotating onto node to be deleted.
                
                tempNode->left=currentnode;
                //put node to be deleted as left node of rotated node
                deleteKey(k,currentnode,tempnode)
            }
        }
    }
}