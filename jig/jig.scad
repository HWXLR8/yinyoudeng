$fn = 50;

include <BOSL2/std.scad>

mid_w = 2.2;
mid_l = 9;
mid_h = 1.5;

ledge_l = 8;
ledge_h = mid_h + 1.75;
ledge_side_h = mid_h + 10.5;

bridge_l = 6.2;

side_w = mid_w;
lside_l = mid_l + bridge_l;
rside_l = 6;
side_h = mid_h + 3;

light_t = 1.5;
light_w = 10 - 0.25;
light_h = ledge_side_h;
light_elevation = 0.5;
light_grip = 0.35;

flush_side = (light_w - mid_w + (light_t * 2)) / 2;

// mid section
cuboid([mid_w, mid_l, mid_h], anchor=BOT) {
  // left side
  attach (LEFT, RIGHT, align=BOT+FRONT) {
    cuboid([flush_side, lside_l, ledge_side_h]) {
      // raised left side
      attach (FRONT, BACK, align=BOT+RIGHT) {
        cuboid([flush_side, ledge_l, ledge_side_h]);
      }
    }
  }

  // raised mid-section
  attach (FRONT, BACK, align=BOT) {
    cuboid([side_w, ledge_l, ledge_h]) {
      // raised right side
      attach (RIGHT, LEFT, align=BOT+FRONT) {
        cuboid([side_w, ledge_l, ledge_side_h]) {
          attach (BACK, FRONT) {
            cuboid([side_w, rside_l, ledge_side_h]);
          }
        }
      }
    }
  }

  attach (BACK, FRONT) {
    // bridge between base and light
    cuboid([mid_w, bridge_l, mid_h]) {
      attach (BACK, FRONT, align=BOT) {
        // light base
        cuboid([light_w, light_t, mid_h]) {
          attach (TOP, BOT, align=RIGHT) {
            // right elevation
            cuboid([(light_w - mid_w) / 2, light_t, light_elevation]);
          }
          attach (TOP, BOT, align=LEFT) {
            // left elevation
            cuboid([(light_w - mid_w) / 2, light_t, light_elevation]);
          }
          attach (BACK, FRONT, align=BOT+RIGHT) {
            // light back-right bar
            cuboid([light_t + light_grip, light_t, light_h]);
          }
          attach (BACK, FRONT, align=BOT+LEFT) {
            // light back-left bar
            cuboid([light_t + light_grip, light_t, light_h]);
          }
          attach (LEFT, RIGHT, align=BOT+FRONT) {
            // left guard
            cuboid([light_t, light_t*2, light_h]);
          }
          attach (RIGHT, LEFT, align=BOT+FRONT) {
            // right guard
            cuboid([light_t, light_t*2, light_h]);
          }
        }
      }
    }
  }
}
