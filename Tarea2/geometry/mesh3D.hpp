// Incluyendo los archivos anteriormente definidos
#include "node.hpp"
#include "condition3D.hpp"
#include "element3D.hpp"
#include "../heap_utilities/minHeap.hpp"
// Incluyendo MinHeap

// Definiendo los enums para las constantes
enum parameter3D{THERMAL_CONDUCTIVITY,HEAT_SOURCE};
enum quantity3D{NUM_NODES,NUM_ELEMENTS,NUM_DIRICHLET,NUM_NEUMANN};

// Declaracion de una clase llamada Mesh3D
class Mesh3D
{
private:
    // arreglos que almacenaran los datos del problemData y las quantidades
    float problemData[2];
    float quantities[4];

    // Punteros dobles que apunta a una matriz dinamica de nodos, elementos, condiciones de dirichlet y condiciones de neumann
    Node **nodes;
    Element3D **elements;
    Condition3D **dirichletConditions;
    Condition3D **neumannConditions;

public:
    //
    Mesh3D() {}

    ~Mesh3D()
    {
        free(nodes);
        free(elements);
        free(dirichletConditions);
        free(neumannConditions);
    }
    void setProblemData(float k, float Q)
    {
        problemData[THERMAL_CONDUCTIVITY] = k;
        problemData[HEAT_SOURCE] = Q;
    }

    float getProblemData(parameter3D position)
    {
        return problemData[position];
    }

    void setQuantities(short numNodes, short numElements, short numDirichlet, short numNeumann)
    {
        quantities[NUM_NODES] = numNodes;
        quantities[NUM_ELEMENTS] = numElements;
        quantities[NUM_DIRICHLET] = numDirichlet;
        quantities[NUM_NEUMANN] = numNeumann;
    }

    int getQuantity(quantity3D position)
    {
        return quantities[position];
    }

    void initArrays()
    {
        nodes = (Node **)malloc(sizeof(Node *) * quantities[NUM_NODES]);
        elements = (Element3D **)malloc(sizeof(Element3D *) * quantities[NUM_ELEMENTS]);
        dirichletConditions = (Condition3D **)malloc(sizeof(Condition3D) * quantities[NUM_DIRICHLET]);
        neumannConditions = (Condition3D **)malloc(sizeof(Condition3D *) * quantities[NUM_NEUMANN]);
    }
    //
    void insertNode(Node *node, short position)
    {
        nodes[position] = node;
        // Llamado de funcion de MinHeap para ordenar los nodos
        heapsort(nodes, position);
    }

    Node *getNode(short position)
    {
        return nodes[position];
        
    }

    void insertElement(Element3D *element, short position)
    {
        elements[position] = element;
    }

    Element3D *getElement(short position)
    {
        return elements[position];
    }

    void insertDirichletCondition(Condition3D *dirichletCondition, short position)
    {
        dirichletConditions[position] = dirichletCondition;
    }

    Condition3D *getDirichletCondition(short position)
    {
        return dirichletConditions[position];
    }

    bool doesNodeHaveDirichletCondition(int id)
    {
        bool ans = false;
        for (int i = 0; i < quantities[NUM_DIRICHLET]; i++)
        {
            if (dirichletConditions[i]->getNode()->get_ID() == id)
            {
                ans = true;
                break;
            }
        }
        return ans;
    }

    void insertNeumannCondition(Condition3D *neumanCondition, short position)
    {
        neumannConditions[position] = neumanCondition;
    }

    Condition3D *getNeumannCondition(short position)
    {
        return neumannConditions[position];
    }

    void report()
    {
        cout << "Information about FEM in 3D\n**********************\n";
        cout << "Problem Data\n**********************\n";
        cout << "Thermal Conductivity: " << problemData[THERMAL_CONDUCTIVITY] << "\n";
        cout << "Heat Source: " << problemData[HEAT_SOURCE] << "\n\n";
        cout << "Quantities\n***********************\n";
        cout << "Number of nodes: " << quantities[NUM_NODES] << "\n";
        cout << "Number of elements: " << quantities[NUM_ELEMENTS] << "\n";
        cout << "Number of dirichlet boundary conditions: " << quantities[NUM_DIRICHLET] << "\n";
        cout << "Number of neumann boundary conditions: " << quantities[NUM_NEUMANN] << "\n\n";
        cout << "List of nodes\n**********************\n";
        cout << "****************************************\n";

        // Imprimiendo los nodos
        for(int i = 0; i<quantities[NUM_NODES];i++)
            cout << "Node:" <<nodes[i]->get_ID() << ", x = "<<nodes[i]->get_x_coordinate() <<", y = "<<nodes[i]->get_y_coordinate() <<", z = "<<nodes[i]->get_z_coordinate() <<"\n";
        cout << "****************************************\n\n";
        cout <<"\nList of Elements\n**********************\n";
        for(int i = 0; i<quantities[NUM_ELEMENTS];i++){
            cout << "Element: "<<elements[i]->get_ID() <<", Node1 = " <<elements[i]->get_node1()->get_ID() <<", Node2 = " <<elements[i]->get_node2()->get_ID() <<", Node3 = " <<elements[i]->get_node3()->get_ID()<<"\n";
            cout <<", Node4 = " <<elements[i]->get_node4()->get_ID() <<"\n";
        } 

        cout<< "\nList of Dirichlet Boundary Conditions\n**********************\n";
        for(int i = 0; quantities[NUM_DIRICHLET];i++){
            cout << "Condition " << i+1 << ": " << dirichletConditions[i]->getNode()->get_ID() << ", Value = " <<dirichletConditions[i]->get_value() <<"\n";
        cout << "\nList of Neumann Boundary Conditions\n**********************\n";
           cout << "Condition " << i+1 << ": " << neumannConditions[i]->getNode()->get_ID() << ", Value = " <<neumannConditions[i]->get_value() <<"\n";
        }
        cout << "\n";
    }
};