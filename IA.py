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

  layers(["bg", "obj", "ui",], "obj"); //definimos las capas en orden
  //"obj" es la capa por defecto
  add([sprite("space"), layer("bg")]); //agregar la imagen en la capa bg

  let score = 0;

  //UI ---> Interfaz gráfica
  ui = add([layer("ui")]);

  ui.on("draw", () => {
    drawText({ text: "Score " + score, size: 14, font: "sink", pos: vec2(8, 24) })
  });


});

go("main");
