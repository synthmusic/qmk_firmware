# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
AUDIO_ENABLE = no           # Audio outputj
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
COMMAND_ENABLE = no        # Commands for debug and configuration
CONSOLE_ENABLE = yes         # Console for debug

NKRO_ENABLE = no            # Enable N-Key Rollover

SPLIT_KEYBOARD = yes

# Disable unsupported hardare
AUDIO_SUPPORTED = no
BACKLIGHT_SUPPORTED = no
MUSIC_ENABLE = no

DEFAULT_FOLDER = redox_sm/right


# optimizations inspired here https://docs.qmk.fm/#/squeezing_avr?id=rulesmk-settings
# see also keymap rules.mk
LTO_ENABLE = yes

AVR_USE_MINIMAL_PRINTF = yes
