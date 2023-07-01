class Element3D{

    private:
        short ID;
        Node *node1;
        Node *node2;
        Node *node3;
        Node *node4;

    public:
        Element3D(short identifier, Node *firstNode, Node *secondNode, Node *thirdNode, Node *fourthNode)
        {
            ID = identifier;
            node1 = firstNode;
            node2 = secondNode;
            node3 = thirdNode;
            node4 = fourthNode;
        }

        void set_ID(short identifier){
            ID = identifier;
        }

        short get_ID(){
            return ID;
        }

        void set_node1(Node* node){
            node1 = node;
        }
        Node* get_node1(){
            return node1;
        }

        void set_node2(Node* node){
            node2 = node;
        }
        //Element3D
        Node* get_node2(){
            return node2;
        }

        void set_node3(Node* node){
            node3 = node;
        }
        Node* get_node3(){
            return node3;
        }

        void set_node4(Node* node){
            node4 = node;
        }
        Node* get_node4(){
            return node4;
        }
};