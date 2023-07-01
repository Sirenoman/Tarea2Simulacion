//Definicion de la clase Condition3D
class Condition3D {
    private:
        //Un puntero de un objeti de tipo Node que lo llamamos node
        Node* node;
        float value;

    public:
        //Constructor de la clase Condition3D que va a recibir dos parametros NodetoAssign y valueToAssign
        Condition3D(Node* nodeToAssign, float valueToAssign){
            node = nodeToAssign;
            value = valueToAssign;
        }

        //Establecer el puntero con el parametro proporcionado
        void set_node(Node* nodeToAssign){
            node = nodeToAssign;
        }

        //Devuelve el puntero
        Node* getNode(){
            return node;
        }

        //Establecer el valor con el parametro proporcionado
        void set_value(float valueToAssign){
            value = valueToAssign;
        }
        //Devuelve el valor de la condicion
        float get_value(){
            return value;
        }



};