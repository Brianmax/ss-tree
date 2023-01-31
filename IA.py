Asteroides4.js
import kaboom from "kaboom"

//creamos el canvas
kaboom({
  scale: 1.5
});

//cargar los assets
loadRoot("sprites/");
loadSprite("space", "space.jpg");
loadSprite("rocket1", "rocket1.png");
loadSprite("rocket2", "rocket2.png");
loadSprite("rocket3", "rocket3.png");
loadSprite("rocket4", "rocket4.png");
loadSprite("ship", "ship.png");
loadSprite("bullet", "bullet.png");
loadSprite("asteroid", "asteroid.png");
loadSprite("asteroid_small1", "asteroid_small1.png");
loadSprite("asteroid_small2", "asteroid_small2.png");
loadSprite("asteroid_small3", "asteroid_small3.png");
loadSprite("asteroid_small4", "asteroid_small4.png");

loadRoot("sounds/");
loadSound("rocket_thrust", "rocket_thrust.wav");
loadSound("laser", "laser.wav");
loadSound("explosion", "explosion.mp3");
loadSound("Steamtech-Mayhem_Looping", "Steamtech-Mayhem_Looping.mp3");


// Menu de inicio opcional
scene("menu",() => {

  layers["bg"];
  add([sprite("space"), layer("bg")]); //agregar la imagen en la capa bg

  add([
    text("Te mueves con las flechas. \n\n Espacio para disparar. ", 
         {
           size: 24,
           width: width(),
         }),
    pos(width()/3, height()/3),
    ]);
  
  wait(2 ,() => {
    go("main");
  });
});


scene("main", () => {  //definimos la escena principal

  const music = play("Steamtech-Mayhem_Looping");
  music.loop();
  
  function pointAt(distance, angle) {
    let radians = -1 * deg2rad(angle);
    return vec2(distance * Math.cos(radians), -distance * Math.sin(radians));
  }

  function asteroidSpawnPoint(){
    return choose([rand(vec2(0), vec2(width(),0)),
                  rand(vec2(0), vec2(0, height())),
                  rand(vec2(0, height()), vec2(width(), height())),
                  rand(vec2(width(), 0), vec2(width(), height()))]);
  }

  layers(["bg", "obj", "ui",], "obj"); //definimos las capas en orden
  //"obj" es la capa por defecto
  add([sprite("space"), layer("bg")]); //agregar la imagen en la capa bg

  let score = 0;

  //UI ---> Interfaz gráfica
  ui = add([layer("ui")]);

  ui.on("draw", () => {

    //dibujar puntaje
    drawText({ text: "Score " + score, size: 14, font: "sink", pos: vec2(8, 24) })

    //dibujar vidas

    drawText({
      text: "Lives: ",
      size: 12,
      font: "sink",
      pos: vec2(8),
    });
    for (let x = 64; x < 64 + (16*player.lives); x+=16){
      drawSprite({
        sprite:"ship",
        pos: vec2(x,12),
        angle: -90,
        origin: "center",
        scale: 0.5,
      });
    }
    
  });

  //La nave

  const player = add([sprite("ship"), pos(160, 120), rotate(0), origin("center"),
  solid(), area(), "player", "mobile", "wraps",
  {
    turn_speed: 3,
    speed: 0,
    max_thrust: 80,
    acceleration: 5,
    deceleration: 4,
    lives: 3,
    can_shoot: true,
    laser_cooldown: 0.5,
    invulnerable: false,
    invulnerability_time: 3,
    animation_frame: 0,
    thrusting: false,
  }
  ])

  //Movimiento

  onKeyDown("left", () => {
    player.angle -= player.turn_speed;  //podemos cambiar la propiedad cuando queramos
  });
  onKeyDown("right", () => {
    player.angle += player.turn_speed;
  });

  onKeyDown("up", () => {
    player.speed = Math.min(player.speed + player.acceleration, player.max_thrust);
    play("rocket_thrust", { volume: 0.05, speed: 2.0 });
  });

  onKeyDown("down", () => {
    player.speed = Math.max(player.speed - player.acceleration, -player.max_thrust);
    play("rocket_thrust", { volume: 0.1, speed: 2.0 });
  });

  //Movimiento Real
  onUpdate("mobile", (e) => {
    e.move(pointAt(e.speed, e.angle));
  })

  onUpdate("wraps", (e) =>{
    if (e.pos.x > width()) {
      e.pos.x = 0;
    }
    if (e.pos.x < 0) {
      e.pos.x = width();
    }
    if (e.pos.y > height()) {
      e.pos.y = 0;
    }
    if (e.pos.y < 0){
      e.pos.y = height();
    }
  });

  //Animación cohetes
  const thrust_animation = ["rocket1", "rocket2", "rocket3", "rocket4"];

  onKeyPress("up", () =>{
    player.thrusting = true;
    player.animation_frame = 0;
  });

  onKeyRelease("up", () => {
    player.thrusting = false;
  });

  onDraw("player",(p) => {
    if (player.thrusting) {
      drawSprite({
        sprite:thrust_animation[p.animation_frame],
        pos: vec2(-p.width/2, 0),
        origin: "center",
      });
    }
  });

  //Añadimos el parpadeo del cohete
  let move_delay = 0.1;
  let timer = 0;

  onUpdate(() => {
    timer += dt();
    if (timer < move_delay) return;
    timer = 0;
    if (player.thrusting){
      player.animation_frame++;
      if (player.animation_frame >= thrust_animation.length){
        player.animation_frame = 0;
      }
    }

    if(player.invulnerable){
      player.hidden = !player.hidden;
    }
  });

  //Disparar cohetes

  onKeyDown("space",() => {
    if (player.can_shoot) {
      add([
        sprite("bullet"),
        pos(player.pos.add(pointAt(player.width/2, player.angle))),
        rotate(player.angle),
        origin("center"),
        area(),
        "bullet",
        "mobile",
        "destructs",
        {
          speed:100
        }
      ]);
      play("laser");
      player.can_shoot = false;
      wait(player.laser_cooldown,() => {
        player.can_shoot = true;
      });
    }
  });

  //Asteroides

  const NUM_ASTEROIDS = 10;

  for (let i=0; i<NUM_ASTEROIDS; i++){
    var spawnPoint = asteroidSpawnPoint();
    var a = add([
      sprite("asteroid"),
      pos(spawnPoint),
      rotate(rand(1,90)),
      origin("center"),
      area(),
      solid(),
      "asteroid",
      "mobile",
      "wraps",
      {
        speed: rand(20,40),
        initializing:true
      }
    ]);
    while (a.isColliding("mobile")){
      spawnPoint = asteroidSpawnPoint();
      a.pos = spawnPoint;
      a.pushOutAll();
    }
    a.initializing = false;
  }

  //Colisiones

  //Jugador - Asteroide

  onCollide("player", "asteroid", (p,a) => {
    if (!a.initializing){
      p.trigger("damage");
    }
  });


  //Cuando el jugador recibe daño
  player.on("damage", () => {
    if (!player.invulnerable){
        player.lives--;
    }
    if (player.lives<=0){
      destroy(player);
    }
    else {
      player.invulnerable = true;
      wait(player.invulnerability_time, () => {
        player.hidden = false;
        player.invulnerable = false;
      });
    }
  });
  
  //Cohete - Asteroide

  onCollide("bullet", "asteroid", (b,a) => {
    if (!a.initializing){
      destroy(b);
      destroy(a);
      play("explosion");
      score = a.is("small") ? score + 2 : score++; //2 puntos por asteroide pequeños, 1 por grande
    }
  });

  //Asteroide - Asteroide

  onCollide("asteroid", "asteroid", (a1,a2) => {
    if (!(a1.initializing || a2.initializing)) {
      val1 = a1.speed;
      val2 = a2.speed;
      wait(0.1,() => {
        a1.speed = -val1;
        a2.speed = -val2;
      });

    }
  });
  //Cuando el jugador muere

  player.on("destroy", () => {
    add([
      text(`GAME OVER\n\nScore: ${score}\n\n[R]estart?`, {size:20}),
      pos(width()/2, height()/2),
      layer("ui")
    ]);
  });


  
  
  //Reiniciar juego

  onKeyPress("r", () => {
    music.stop();
    go("main");
  });

  //Dividir asteroides

  on("destroy", "asteroid", (a) => {
    //crear 4 asteroides pequeños 
    if (!a.is("small")) {
      positions = [a.pos.add(vec2(a.width/4, -a.height/4)),
                  a.pos.add(vec2(-a.width/4, -a.height/4)),
                  a.pos.add(vec2(-a.width/4, a.height/4)),
                  a.pos.add(vec2(a.width/4, a.height/4))];

      rotations = [16, 34, 65, 87];

      for (let i=0; i < positions.length; i++) {
        var s = add([
          sprite(`asteroid_small${i+1}`),
          pos(positions[i]),
          rotate(rotations[i]),
          origin("center"),
          area(),
          solid(),
          "asteroid",
          "small",
          "mobile",
          "wraps",
          {
            speed: rand(15,25),
            initializing: false
          }
        ]);
        s.pushOutAll();
      }
    }
  });

  
});

go("menu"); //si se usa el menú
//go("main");
