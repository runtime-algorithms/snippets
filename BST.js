//remove function incomplete at the moment

class LLNode{ //linked list node
	next=null;
	constructor(value){this.value=value}
}
class BSTNode{ //binary search tree node
	height=1;
	next=null;
	left=null;
	right=null;
	parent=null;
	constructor(key,value){
		this.key = key;
		this.value = new LLNode(value);
	}
}

class BST {
	root=null;
	constructor(){}
	height(N){return N?N.height:0}
	max(a,b){return a>b?a:b}
	rightRotate(y){
		var x = y.left;
		var T2 = x.right;
		
		// Perform rotation
		x.right = y;
		y.left = T2;
		
		// Update heights
		y.height = this.max( this.height(y.left),this.height(y.right) )+1;
		x.height = this.max( this.height(x.left),this.height(x.right) )+1;
		
		// Update parents
		if(T2) T2.parent = y;
		y.parent = x;
		
		// Return new root
		return x;
	}
	leftRotate(x){
		var y = x.right;
		var T2 = y.left;
		
		// Perform rotation
		y.left = x;
		x.right = T2;
		
		// Update heights
		x.height = this.max( this.height(x.left),this.height(x.right) )+1;
		y.height = this.max( this.height(y.left),this.height(y.right) )+1;
		
		// Update parents
		if(T2) T2.parent = x;
		x.parent = y;

		// Return new root
		return y;
	}
	getBalance(N){
		if(N===null) return 0;
		return this.height(N.left) - this.height(N.right);
	}
	#insert(key, data, node=this.root){
		if(node===null) return new BSTNode(key,data);
		if(key < node.key){
			node.left = this.#insert(key,data,node.left);
			node.left.parent = node;
		}
		else if(key > node.key){
			node.right = this.#insert(key,data,node.right);
			node.right.parent = node;
		}
		//else we have a node of the same key and we add to its value stack
		else{
			let top=new LLNode(data);
			top.next=node.value;
			node.value=top;
			return node;
		}
		
		node.height = 1+this.max( this.height(node.left),this.height(node.right) );
		var balance = this.getBalance(node);
		
		if(balance>1 && key<node.left.key) return this.rightRotate(node); //left left case
		if (balance<-1 && key>node.right.key) return this.leftRotate(node); //right right case
		if(balance>1 && key>node.left.key)
			return (node.left=this.leftRotate(node.left),  this.rightRotate(node)); //left right case
		if (balance<-1 && key<node.right.key)
			return (node.right=this.rightRotate(node.right),  this.leftRotate(node)); //right left case
		
		return node;
	}
	#delete(key, node=this.root){}
	#remove(key, data, node=this.root){}
	insert(key,data,node){
		this.root=this.#insert(key,data,node);
		return this.root;
	}
	
	
	//utility functions begin
	set(key,data){
		let item=this.get(key);
		if(item) item.value=null;
		this.root=this.#insert(key,data);
		return this.root;
	}
	get(key){
		let curr=this.root;
		while(curr!==null && curr.key!==key){
			if(curr.key<key) curr=curr.right;
			else curr=curr.left;
		}
		return curr;
	}
	minimum(){
		let curr=this.root;
		while(curr.left!==null) curr=curr.left;
		return curr;
	}
	maximum(){
		let curr=this.root;
		while(curr.right!==null) curr=curr.right;
		return curr;
	}
	preOrder(node=this.root){
		if(node===null) return;
		console.log(node.key);
		this.preOrder(node.left);
		this.preOrder(node.right);
	}
	inOrder(node=this.root){
		if(node===null) return;
		this.inOrder(node.left);
		console.log(node.key);
		this.inOrder(node.right);
	}
	postOrder(node=this.root){
		if(node===null) return;
		this.postOrder(node.left);
		this.postOrder(node.right);
		console.log(node.key);
	}
	inOrderSuccessor (item=null){
		if(item==null) return null; //no successor because NOTHING
		if(item.right===null){ //if nothing to the right
			while(item.parent!==null && item.parent.right===item) item=item.parent;
			return item.parent; //successor or NULL(if item was originally the last element)
		}
		item=item.right;
		while(item.left!==null) item=item.left;
		return item;
	}
	justGreater(key){
		//returns the node with the smallest key in the BST that is greater than the given one (or null)
		let curr=this.root, winner=this.root;
		if(curr==null) return curr; //which is null
		while(curr.key<=key){
			if(curr.right===null) return null; //no node.key > key in BST
			curr=curr.right;
		}
		while(curr.key>key){
			winner=curr; //save it for when traversal goes under
			if(curr.left===null) return curr; //nothing lower that satisfies the condition
			curr=curr.left;
			while(curr.key<key){
				if(curr.right===null) return winner; //no node.key > key in SUBroot, return last item where node.key > key
				curr=curr.right;
			}
		}
		return winner; //I don't even think I need this line but just in case?
	}
	justSmaller(key){
		//returns the node with the greatest key in the BST that is smaller than the given one (or null)
		let curr=this.root, winner=this.root;
		if(curr===null) return curr; //which is null
		while(curr.key>=key){
			if(curr.left===null) return null; //no node.key < key in BST
			curr=curr.left;
		}
		while(curr.key<key){
			winner=curr; //save it for when traversal goes under
			if(curr.right===null) return curr; //nothing lower that satisfies the condition
			curr=curr.right;
			while(curr.key>key){
				if(curr.left===null) return winner; //no node.key > key in SUBroot, return last item where node.key > key
				curr=curr.left;
			}
		}
		return winner; //I don't even think I need this line but just in case?
	}
	//utility functions end
}








//example usage
var tree = new BST(), arr=[10,20,30,40,50,25];
for(let i=0;i<arr.length;i++)
	tree.set(arr[i],Math.random());
tree.preOrder();
