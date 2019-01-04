#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



void log (std::string _string){
  std::cout << _string << "\n";
}
class welt{
public:
welt(){

  log("init 2dArray");
  for(int i = 1; i < grid_size-1 ; i++){
   for(int j = 1; j < grid_size-1 ; j++){
      cellgrid[j][i] = false;
    }
  }

}

  bool cellgrid[100][100];
  bool new_cellgrid[100][100];

  int inc_grid[100][100];
  int inc_num = 10;

  int grid_size = 58;
  int cellsize = 8;
  bool inc_enabled = false;

int check_n(int _x,int _y){
  int counted = 0;

//_1a_1b_1c
//_2a_2b_2c
//_3a_3b_3c

//_1  
  if(cellgrid[_x-1][_y-1]==true){counted++;}
  if(cellgrid[_x][_y-1]  ==true){counted++;}
  if(cellgrid[_x+1][_y-1]==true){counted++;}
//_2
  if(cellgrid[_x-1][_y]  ==true){counted++;}  
  if(cellgrid[_x+1][_y]  ==true){counted++;}
//_3
  if(cellgrid[_x-1][_y+1]==true){counted++;}
  if(cellgrid[_x][_y+1]  ==true){counted++;}
  if(cellgrid[_x+1][_y+1]==true){counted++;}

  return counted;
}

void update(int j,int i){
  int nbs = check_n(j,i);
  //Rules of the simulation
  if(nbs<2){new_cellgrid[j][i]=false;}
  if(cellgrid[j][i]==true&&nbs==2||cellgrid[j][i]==true&&nbs==3){
    new_cellgrid[j][i]=true; inc_grid[j][i]+=10;
  }
  //if(nbs==3){new_cellgrid[j][i]=true; inc_grid[j][i]+=10;}
  if(nbs==1){new_cellgrid[j][i]=true;			 }
  if(nbs>3){new_cellgrid[j][i]=false; inc_grid[j][i]+=10;}
  //inc
  if(inc_enabled){
    if(inc_grid[j][i]>inc_num){new_cellgrid[j][i]=true;}
  }

}

  void draw_c(int _x,int _y,sf::RenderWindow &window){
    sf::RectangleShape box(sf::Vector2f(cellsize,cellsize));
    if(cellgrid[_x][_y]==true){box.setFillColor(sf::Color::Green);}
    else{box.setFillColor(sf::Color(30,30,30));}
    if(inc_enabled){
      if(inc_grid[_x][_y]>inc_num){
        box.setFillColor(sf::Color(0,inc_grid[_x][_y]/10,0));
      }
    }
    box.setPosition(sf::Vector2f(_x*cellsize,_y*cellsize));
    window.draw(box);
  }

};


int main(){
  
log("Starting Simulation");

sf::RenderWindow window(sf::VideoMode(400,400),"test");
window.setFramerateLimit(60);

log("Array");
welt world;
int interval = 1;
int time = 0;
int tick = 0;
int skipp = 3;
bool paused=false;

sf::Font font;
if(!font.loadFromFile("fixedsys.ttf")){}

sf::Text text;
text.setFont(font);
text.setPosition(sf::Vector2f(20,2));
text.setString("PAUSED");
text.setFillColor(sf::Color::Black);

sf::Text text;
text.setFont(font);
text.setPosition(sf::Vector2f(20,2));
text.setString("FPS:");
text.setFillColor(sf::Color::Black);


int pos_x=skipp;
int pos_y=skipp;
int movetick=0;
bool m_right=false;
bool m_left=false;
bool m_up=false;
bool m_down=false;
bool m_enter=false;
bool f_enter=false;
std::string pltype = "Life";

while(window.isOpen()){
	sf::Event event;
	tick++;
	int sp=0;
	while(window.pollEvent(event)){
	  if(event.type == sf::Event::Closed){
	    window.close();
	  }
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
	    window.close();
	  }
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
	      m_left=true;
	  }else{m_left=false;}
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
	      m_right=true;
	  }else{m_right=false;}
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
	      m_up=true;
	  }else{m_up=false;}
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
	      m_down=true;
	  }else{m_down=false;}

	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)){
	    for(int i = pos_x-3; i < pos_x+3 ; i++){
              for(int j = pos_y-3; j < pos_y+3 ; j++){
	        world.inc_grid[i][j] = 0;
	        world.cellgrid[i][j] = false;
	      }
	    }
	    world.inc_grid[pos_x][pos_y] = 0;
	    world.cellgrid[pos_x][pos_y] = false;
	  }
	  
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
		  m_enter=true;
	     
	  }else{m_enter=false;}
	
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            if(sp){
	      bool Break = false;
              if(paused==true){paused=false; Break=true;}
	      if(paused==false&&Break==false){paused=true;}
	    }
	    sp=1;
	  }else{sp=0;}
	  
	}
	
  window.clear();
  int m_delay = 2;
  
if(movetick>m_delay){
  movetick=0;
  if(m_enter){
    if(!f_enter){
      f_enter=true;
      bool Break = false;
      if(world.cellgrid[pos_x][pos_y]==true){
        world.cellgrid[pos_x][pos_y]=false; Break=true;}
      if(world.cellgrid[pos_x][pos_y]==false&&Break==false){
        world.cellgrid[pos_x][pos_y]=true;
    }
   }
  }
  if(m_down) { pos_y++; f_enter=false; }
  if(m_up)   { pos_y--; f_enter=false; }
  if(m_left) { pos_x--; f_enter=false; }
  if(m_right){ pos_x++; f_enter=false; }
}
  if(m_down||m_right||m_up||m_left){movetick++; f_enter=false;}else{movetick=m_delay+1;}

if(paused == false){
  time++;
  for(int i = skipp; i < world.grid_size-skipp ; i++){
    for(int j = skipp; j < world.grid_size-skipp ; j++){
      world.draw_c(j,i,window);
      if(time==interval){
        world.update(j,i);
	
        //world.cellgrid[j][i] = world.new_cellgrid[j][i];
      }
    }
  }

  if(time==interval){ time=0;
   for(int i = skipp; i < world.grid_size-skipp ; i++){
    for(int j = skipp; j < world.grid_size-skipp ; j++){
     
        world.cellgrid[j][i] = world.new_cellgrid[j][i];
    }
   }
  }

}else{
  for(int i = skipp; i < world.grid_size-skipp ; i++){
    for(int j = skipp; j < world.grid_size-skipp ; j++){
      world.draw_c(j,i,window);
      
    }
  }
  sf::RectangleShape yellowbox(sf::Vector2f(300,15));
  yellowbox.setFillColor(sf::Color::Yellow);
  yellowbox.setPosition(sf::Vector2f(20,2));
  window.draw(yellowbox);
  text.setCharacterSize(14);
  window.draw(text);

  text_fps.setText("FPS:" + window.
  text_fps.setCharacterSize(14);
  window.draw(text_fps);

  sf::RectangleShape sbox(sf::Vector2f(world.cellsize-4,world.cellsize-4));
  if(tick%2==1){sbox.setFillColor(sf::Color::Red);}else{
  sbox.setFillColor(sf::Color::Cyan);}
  sbox.setPosition(sf::Vector2f(pos_x*world.cellsize+2,pos_y*world.cellsize+2));
  window.draw(sbox);
}

  window.display();

}
  return 0;
}
