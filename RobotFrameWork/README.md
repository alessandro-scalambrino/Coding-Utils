# Remote GPIO Control Robot Tests
gpio.robot --> The tests connect via SSH to a remote device and execute commands to control GPIO pins, allowing automated verification of GPIO states.

## Usage

Edit the test suite or pass variables to set:

```robot
*** Variables ***
${HOST}        <target-ip-or-hostname>
${USERNAME}    <ssh-username>
${PASSWORD}    <ssh-password>
${GPIO_PIN}    <gpio-pin-number>
```
or pass the variables via cmdline:
```
robot -v HOST:<target-ip-or-hostname> -v USERNAME:<ssh-username> -v PASSWORD:<ssh-password> -v GPIO_PIN:<gpio-pin-number> gpio.robot
```
# Module Insertion Robot Test

## Usage

Edit the test suite or pass variables to set:
gpio.robot --> The tests connect via SSH to a remote device and execute commands to load out-of-tree kernel modules, allowing automated verification of modules loading/unloading.

```robot
*** Variables ***
${HOST}        <target-ip-or-hostname>
${USERNAME}    <ssh-username>
${PASSWORD}    <ssh-password>
${KO_PATH}    <your remote .ko file path>
${MODULE_NAME}    <your module name>

```
