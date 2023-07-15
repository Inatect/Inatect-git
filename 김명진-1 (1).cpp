#include <iostream>
#include <vector>
#include <limits>
using namespace std; 

class ShapeCal {
public:
    void run() {
        int numShapes = getNumShapes();  // ������ ������ �Է¹޴� �Լ� ȣ��
        inputShapes(numShapes);  // �������� ������ �Է¹޴� �Լ� ȣ��
        calDulraes();  // ������ �ѷ��� ����ϴ� �Լ� ȣ��
        printResult();  // ����� ����ϴ� �Լ� ȣ��
    }

private:
    struct Shape {
        int type; // ������ ������ ��Ÿ���� ����
        vector<double> lengths; // ������ �� ���̸� �����ϴ� ����
        double dulrae;
    };

    vector<Shape> shapes;  // �������� �����ϴ� ����

    int getNumShapes() {
        int numShapes;
        while (true) {
            cout << "������ ������ �Է��ϼ��� (0�� �Է��ϸ� ����): ";
            cin >> numShapes;

            // �Էµ� ������ ������ 0 �̻����� Ȯ���մϴ�.
            if (numShapes >= 0) {
                break;  // �ùٸ� ���� �Էµ� ��� �ݺ����� �����մϴ�.
            } else {
                cout << "����: ������ ������ 0 �̻��̾�� �մϴ�." << endl;
            }
        }
        return numShapes;
    }

    int getShapeType() {
        int shapeType;
        while (true) {
            cout << "������ ������ �Է��ϼ��� (1: ��, 2: ���簢��, 3: �ﰢ��): ";
            cin >> shapeType;

            // �Էµ� ������ ������ 1���� 3 �������� Ȯ���մϴ�.
            if (shapeType >= 1 && shapeType <= 3) {
                break;  // �ùٸ� ���� �Էµ� ��� �ݺ����� �����մϴ�
            } else {
                cout << "����: 1���� 3 ������ ���� �Է����ּ���." << endl;
            }
        }
        return shapeType;
    }


    vector<double> getShapeLengths(int shapeType) {
        int numLengths;
        switch (shapeType) {
            case 1: // ��
                numLengths = 1;
                break;
            case 2: // ���簢��
                numLengths = 2;
                break;
            case 3: // �ﰢ��
                numLengths = 3;
                break;
        }

        vector<double> lengths(numLengths);
        for (int i = 0; i < numLengths; ++i) {
            cout << "���� #" << (i + 1) << ": ";
            cin >> lengths[i];
        }
        return lengths;
    }

    bool isTriangle(const vector<double>& lengths) {
        double maxDulrae = numeric_limits<double>::min();
        double sumLengths = 0.0;

        // �־��� ���� �� ���� �� ���̿� ������ ���� ����� 
        for (vector<double>::const_iterator it = lengths.begin(); it != lengths.end(); ++it) {
            double length = *it;
            maxDulrae = max(maxDulrae, length);
            sumLengths += length;
        }

        // �ﰢ���� �Ǵ� ���� Ȯ��
        return (maxDulrae < sumLengths - maxDulrae);
    }

    void inputShapes(int numShapes) {
        for (int i = 0; i < numShapes; ++i) {
            Shape shape;
            shape.type = getShapeType();
            shape.lengths = getShapeLengths(shape.type);

            // �ﰢ���� ��� ���� �˻�
            if (shape.type == 3 && !isTriangle(shape.lengths)) {
                cout << "����: �ﰢ���� �ƴ� �����Դϴ�. �ٽ� �Է����ּ���." << endl;
                --i;  // �ٽ� �Է� �ޱ� ���� i�� ���ҽ�Ŵ
                continue;
            }

            shapes.push_back(shape);
        }
    }

    void calDulraes() {
        for (vector<Shape>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
            Shape& shape = *it;
            double dulrae = 0.0;

            switch (shape.type) {
                case 1: // ��
                    dulrae = 2 * 3.14159 * shape.lengths[0];
                    break;
                case 2: // ���簢��
                    dulrae = 2 * (shape.lengths[0] + shape.lengths[1]);
                    break;
                case 3: // �ﰢ��
                    dulrae = shape.lengths[0] + shape.lengths[1] + shape.lengths[2];
                    break;
            }

            shape.dulrae = dulrae;
        }
    }

    void printResult() { // �������� ��ȸ�ϸ鼭 ������ ����մϴ�
        for (vector<Shape>::iterator it = shapes.begin(); it != shapes.end(); ++it) { 
            const Shape& shape = *it; // ���� ������ ���� ���۷����� �����ɴϴ�.
            string shapeName;
            switch (shape.type) { // ������ ������ ���� �̸��� �����մϴ�.
                case 1:
                    shapeName = "��";
                    break;
                case 2:
                    shapeName = "���簢��";
                    break;
                case 3:
                    shapeName = "�ﰢ��";
                    break;
            }
            cout << shapeName << " ("; // ������ �̸��� ����մϴ�.
            for (vector<double>::size_type i = 0; i < shape.lengths.size(); ++i) {
                cout << "���� #" << (i + 1) << ": " << shape.lengths[i]; // ������ ���̰� �ƴ� ��� ��ǥ�� ����մϴ�.
                if (i != shape.lengths.size() - 1) {
                    cout << ", ";
                }
            } // �ѷ� ���̸� ����մϴ�.
            cout << ") - �ѷ� ����: " << shape.dulrae << endl;
        }
    }
};

int main() {
    ShapeCal cal;
    cal.run();

    return 0;
}

