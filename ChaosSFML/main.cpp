#include  <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <Windows.h>
#include <sstream>

using namespace std;

class Point2D {
private:
	double x_;
	double y_;
public:
	Point2D() {
		x_ = 0;
		y_ = 0;
	}
	Point2D(double a, double b) {
		x_ = a;
		y_ = b;
	}
	~Point2D() {}
	double get_x() const { 
		return x_; 
	}
	double get_y() const { 
		return y_; 
	}
	void set_x(double x) 
	{ x_ = x; 
	}
	void set_y(double y) { 
		y_ = y; 
	}
	friend Point2D *sum(Point2D *o1, Point2D *o2);
	friend Point2D *VxA(double t, Point2D *v, Point2D *tmp);
};
Point2D *sum(Point2D *o1, Point2D *o2) {  //сумма двух векторов
	(o1)->set_x(o1->get_x() + o2->get_x());
	(o1)->set_y(o1->get_y() + o2->get_y());
	return o1;
}

Point2D *VxA(double t, Point2D *v, Point2D *tmp) {  //век на число
	//Point2D aHelp = v;
	tmp->set_x(v->get_x() * t);
	tmp->set_y(v->get_y() * t);
	return tmp;
}

using namespace sf;

int main()
{
	// ввод высоты и ширины окна
	int H, W;
	cout << "Enter width and height of window, 800x800 recommended:" << endl;
	cin >> W >> H;
	//создание необходимых переменных
	Point2D *v = new Point2D(); // скорость и ускорение
	Point2D *a = new Point2D();
	Point2D *v2 = new Point2D();
	Point2D *a2 = new Point2D();
	double l = 1;
	double l2 = 1;
	Point2D *pnt = new Point2D(0, -l);  // положение шариков
	Point2D *pnt2 = new Point2D(0, -l - l2);
	double g = 10;
	double T2 = 0;
	double T1 = 0;
	double D = 0.01; //0.00000001; // вязкость воздуха
	double K = 1000000; //1000000;
	Point2D *aHelp = new Point2D();
	//Ввод жесткости пружины (10000 - твёрдый стержень)
	cout << "Enter spring rate (>10000 - solid rod, [0.5;10] - recommended for springs, [100;1000] - not recommended):" << endl;
	cin >> K;
	K *= 100;
	//cout << x1 << "   " << y1 << endl;
	a->set_y(T1 * pnt->get_y() + T2 * (pnt->get_y() - pnt2->get_y()) + g - v->get_y() * abs(v->get_y()) * D);
	a->set_x(T1 * pnt->get_x() + T2 * (pnt->get_x() - pnt2->get_x()) - v->get_x() *abs(v->get_x()) * D);
	
	a2->set_y(T2 * (-pnt->get_y() + pnt2->get_y()) + g - v2->get_y() * abs(v2->get_y()) * D);
	a2->set_x(T2 * (-pnt->get_x() + pnt2->get_x()) - v2->get_x() * abs(v2->get_x()) * D);
	
	//задание начальной скорости шарикам
	v->set_x(0.00001);
	v->set_y(0.00001);
	v2->set_x(0.9999);
	v2->set_y(0.00001);	
	//шаг времени
	double t = 0.000001; //0.00000006;  
	
	float x1, x2, y1, y2;
	x1 = (float)(pnt->get_x()) * 100 + (float)(W/2);
	y1 = ((float)(pnt->get_y()) * 100) + (float)(H/2);
	x2 = (float)(pnt2->get_x()) * 100 + (float)(W / 2);
	y2 = (float)(pnt2->get_y()) * 100 + (float)(H / 2);
	sf::RenderWindow window(sf::VideoMode(W, H), "Okonnoe okno okonnogo okna");
	
	//создание шарика 1 (шейп) и смещённого центра координат
	float r = 5; //радиус шарика 1
	sf::CircleShape shape(r);
	float rc = 2;
	sf::CircleShape centre(rc);
	centre.setPosition(sf::Vector2f(sf::Vector2f(W/2 - rc, H/2 - rc)));
	centre.setFillColor(sf::Color::White);
	shape.setFillColor(sf::Color::Yellow);

	//Создание стержня 1
	sf::VertexArray line(Lines, 2);
	line[0].position = Vector2f(W/2, H/2);
	line[1].position = Vector2f(x1, y1);
	line[0].color = Color::Blue;
	
	//Создание стержня 2
	sf::VertexArray line2(Lines, 2);
	line2[0].position = Vector2f(x1, y1);
	line2[1].position = Vector2f(x2, y2);
	line2[0].color = Color::Green;
	
	//создание шарика 2 (шейп2)
	float r2 = 5; //радиус шарика 2
	sf::CircleShape shape2(r2);
	shape2.setFillColor(sf::Color::Red);
	
	int i = 0;
	x1 = (float)(pnt->get_x()) * 100 + (float)(W / 2);
	y1 = ((float)(pnt->get_y()) * 100) + (float)(H / 2);
/*  ДОБАВИТЬ ВЫВОД СКОРОСТЕЙ, КООРДИНАТ И УСКОРЕНИЙ НА ЭКРАН
	std::ostringstream curV;    // объявили переменную
	curV << v->get_x();		//занесли в нее число очков, то есть формируем строку
	text.setString("Собрано камней:" + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
	text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры
	window.draw(text);//рисую этот текст
*/
	while (window.isOpen()) {
		//Sleep(50);
		for (int j = 0; j < 1000; j++) {
			i++;
			T2 = -(l2 - 1) * K / l2;
			T1 = -(l - 1) * K / l;

			a->set_y(T1 * pnt->get_y() + T2 * (pnt->get_y() - pnt2->get_y()) + g - v->get_y() * abs(v->get_y()) * D);
			a->set_x(T1 * pnt->get_x() + T2 * (pnt->get_x() - pnt2->get_x()) - v->get_x() *abs(v->get_x()) * D);

			a2->set_y(T2 * (-pnt->get_y() + pnt2->get_y()) + g - v2->get_y() * abs(v2->get_y()) * D);
			a2->set_x(T2 * (-pnt->get_x() + pnt2->get_x()) - v2->get_x() * abs(v2->get_x()) * D);

			aHelp = VxA(t, a, aHelp);
			v = sum(v, aHelp);
			aHelp = VxA(t, a2, aHelp);
			v2 = sum(v2, aHelp);
			aHelp = VxA(t, v, aHelp);

			pnt = sum(pnt, aHelp);
			aHelp = VxA(t, v2, aHelp);
			pnt2 = sum(pnt2, aHelp);

			l = sqrt(pnt->get_x() * pnt->get_x() + pnt->get_y() * pnt->get_y());
			l2 = sqrt((pnt->get_x() - pnt2->get_x()) * (pnt->get_x() - pnt2->get_x()) + (pnt->get_y() - pnt2->get_y()) * (pnt->get_y() - pnt2->get_y()));
		}
		//Прорисовка маятника(до конца цикла)
		//Обработка закрытия окна
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Координаты первого шарика и их присваивание фигурам
		x1 = (float)(pnt->get_x()) * 100 + (float)(W / 2);
		y1 = ((float)(pnt->get_y()) * 100) + (float)(H / 2);
		shape.setPosition(sf::Vector2f(x1-r, y1-r));
		line[1].position = (sf::Vector2f(x1, y1));
		
		//Второй шар
		x2 = (float)(pnt2->get_x()) * 100 + (float)(W / 2);
		y2 = (float)(pnt2->get_y()) * 100 + (float)(H / 2);
		shape2.setPosition(sf::Vector2f(x2 - r2, y2 - r2));
		line2[0].position = Vector2f(x1, y1);
		line2[1].position = Vector2f(x2, y2);
		//if (i % 200 == 0) cout << ".\n";
		/*if (i % 200 == 0) {
			cout << "x1 = " << x1 << "  y1 = " << y1 << endl;
			cout << "x2 = " << x2 << "  y2 = " << y2 << endl;
		}*/
		window.clear();				
		window.draw(line);
		window.draw(shape); 
		window.draw(line2);
		window.draw(shape2);
		window.draw(centre);
		window.display();		
	}
	return 0;
}

