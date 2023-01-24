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

scene("main", () => {  //definimos la escena principal

  function pointAt(distance, angle) {
    let radians = -1 * deg2rad(angle);
    return vec2(distance * Math.cos(radians), -distance * Math.sin(radians));
  }


  layers(["bg", "obj", "ui",], "obj"); //definimos las capas en orden
  //"obj" es la capa por defecto
  add([sprite("space"), layer("bg")]); //agregar la imagen en la capa bg

  let score = 0;

  //UI ---> Interfaz gráfica
  ui = add([layer("ui")]);

  ui.on("draw", () => {
    drawText({ text: "Score " + score, size: 14, font: "sink", pos: vec2(8, 24) })
  });

  //La nave

  const player = add([sprite("ship"), pos(160, 120), rotate(0), origin("center"),
  solid(), area(), "player", "mobile", "wraps",
  {
    turn_speed: 3,
    speed: 0,
    max_thrust: 48,
    acceleration: 2,
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
  })

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


  
});

go("main");
