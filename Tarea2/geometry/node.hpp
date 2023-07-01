// Declaracion de una clase llamada Node
class Node{
    private:
        // Declaración de un indentificador
        short ID;

        // Declaración de las coordenadas
        float xCoordinate;
        float yCoordinate;
        float zCoordinate;

    public:
        // Constructor de la clase Node
        // Al llamarse se debera de pasar los cuatros parametros
        Node(short identifier, float x_value, float y_value, float z_value){
            ID = identifier;
            xCoordinate = x_value;
            yCoordinate = y_value;
            zCoordinate = z_value;
        }

        // Retorna el valor del identificador de tipo short
        short get_ID()
        {
            return ID;
        }

        // Asigna o establece el identificador del nodo proporcionado
        void set_ID(short identifier3D)
        {
            ID = identifier3D;
        }

        // Establece la coordenada que nos va a servir para el eje x
        void set_x_coordinate(float x_value)
        {
            xCoordinate = x_value;
        }

        // Devuelve el valor de nuestra coordenada x
        float get_x_coordinate()
        {
            return xCoordinate;
        }

        // Establece la coordenada que nos va a servir para el eje y
        void set_y_coordinate(float y_value)
        {
            yCoordinate = y_value;
        }
        // Devuelve el valor de nuestra coordenada y
        float get_y_coordinate()
        {
            return yCoordinate;
        }

        // Establece la coordenada que nos va a servir para el eje z
        void set_z_coordinate(float z_value)
        {
            zCoordinate = z_value;
        }

        // Devuelve el valor de nuestra coordenada z
        float get_z_coordinate()
        {
            return zCoordinate;
        }

};
