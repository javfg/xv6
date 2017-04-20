#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

// Padding: sirve para que el programa ocupe 2 páginas. Así sabemos cuanto ocupa seguro.
char* padding = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed viverra, lacus quis accumsan laoreet, urna felis tincidunt dolor, at laoreet tortor nisi mollis tellus. Etiam hendrerit mauris a metus ultrices tincidunt. Curabitur ut ultricies mauris, sed pellentesque tortor. Aliquam erat volutpat. Fusce in sodales ante. Duis imperdiet quam et posuere tincidunt. Morbi tempus feugiat lectus ut efficitur. Nullam ac sem id leo molestie pulvinar. Suspendisse posuere blandit elit vel commodo. Nam rhoncus sed nibh nec vestibulum. Mauris lorem nisi, tincidunt non congue id, maximus et lacus. Vestibulum auctor fringilla molestie. Proin non mi in urna rhoncus blandit nec vel velit. Etiam pretium velit vitae turpis pulvinar, sed suscipit neque sodales. Phasellus non enim hendrerit, semper quam feugiat, accumsan purus. Donec eget felis auctor, porttitor ipsum tristique, aliquam augue. Aliquam eget aliquam arcu. Quisque tincidunt ante tellus, et convallis ipsum bibendum a. Nulla eu convallis enim, non aliquet metus. Sed enim nunc, ultrices et arcu eu, consequat gravida urna. Sed eget cursus turpis. Vestibulum vitae turpis sit amet purus mattis pretium. Cras suscipit metus elit, at sollicitudin mauris vehicula vel. Vestibulum eu ligula et leo aliquet eleifend. Fusce tincidunt, erat quis rutrum gravida, felis velit venenatis justo, nec vulputate lectus orci vel ex. Donec non luctus justo. Donec a nulla justo. Nulla facilisi. Sed malesuada tortor nec purus posuere, in dictum ante vehicula. Quisque lobortis nisl vitae felis eleifend rutrum. Aenean feugiat turpis ac ipsum eleifend commodo. Pellentesque ut orci tellus. Integer euismod sodales justo at congue. Fusce nec justo scelerisque, euismod nunc vitae, vehicula sapien. Maecenas interdum erat at magna condimentum vehicula. Integer porta placerat dolor eu ultricies. In pellentesque dolor ac velit ultrices euismod. Fusce pharetra urna venenatis tortor sollicitudin congue. Donec pulvinar venenatis erat eget imperdiet. Vestibulum nunc justo, efficitur ac aliquet sed, elementum nec massa. Duis sollicitudin mi sit amet ipsum lacinia ultrices. Duis et dapibus dui, a pellentesque libero. Ut arcu tellus, feugiat eget lorem at, blandit ornare purus. Curabitur ut felis id diam porttitor aliquam. Suspendisse nisi nibh, porta non ex et, feugiat suscipit metus. Nam id dui eget erat tristique vestibulum. Etiam quis ipsum erat. Morbi eget mi sem. Vivamus blandit dignissim dapibus. Aenean sodales at ligula vitae ultricies. Proin efficitur nibh sit amet felis tempor rutrum. Pellentesque molestie urna tortor, eu mattis est egestas nec. Vestibulum commodo accumsan nulla a hendrerit. Vestibulum interdum lacus in sapien ultricies convallis. Nunc id orci ultricies, egestas est in, imperdiet felis. Pellentesque ut justo lacinia, blandit tellus et, ullamcorper libero. Mauris nec risus eget nisl dictum vulputate. Phasellus interdum ornare libero, et cursus elit accumsan condimentum. Phasellus sed erat mattis, interdum nisl eget, lacinia mi. Praesent tempus massa nibh, ut consequat nulla tincidunt rutrum. Phasellus egestas massa sed elit imperdiet hendrerit. Integer eget faucibus lacus. Sed vestibulum mollis metus eget facilisis. Aliquam consequat egestas sagittis. Quisque luctus molestie hendrerit. Integer mollis, augue ut sagittis tincidunt, nisl quam consectetur eros, et eleifend metus ligula a enim. Nam dictum nunc et urna pretium, vitae accumsan lacus tempus. Sed ullamcorper, tellus vel bibendum sodales, nisl urna hendrerit ipsum, et imperdiet turpis justo at leo. Vestibulum vel nibh in massa vestibulum sollicitudin vel a neque. Phasellus nec odio a magna elementum tincidunt. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Maecenas maximus metus eget velit dictum semper. Mauris nec pharetra ex. Cras porttitor dui egestas magna vehicula, a auctor odio aliquet. Proin pharetra, dui ut porttitor imperdiet, nunc sapien porttitor quam, lobortis volutpat risus lorem ut erat. Aliquam eu rutrum urna. Donec vitae justo ultrices, porttitor diam id, commodo libero. Aliquam at elit vel amet.";

void
popo(int i) {
  while(1) {
    char* mensaje = "HOLA, SOY LA FUNCION NUMERO ";
    printf(1, "%s %d\n", mensaje, i);
    i++;
    popo(i);
  }
}


int 
main (int argc, char *argv[]) {
  int i = 0;
  popo(i);

  exit();
}
