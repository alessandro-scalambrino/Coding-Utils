*** Settings ***
Library    SSHLibrary
Library    Process
Suite Setup     Open SSH Session
Suite Teardown  Close Connection

*** Variables ***
${HOST}        None
${USERNAME}    None
${PASSWORD}    None
${GPIO_PIN}    None


*** Test Cases ***
Blink LED Over SSH using WiringPi
    [Tags]    skip
    Execute Command    gpio mode ${GPIO_PIN} out

    Execute Command    gpio write ${GPIO_PIN} 1
    Verifica Stato GPIO    ${GPIO_PIN}    1
    Sleep              1s

    Execute Command    gpio write ${GPIO_PIN} 0
    Verifica Stato GPIO    ${GPIO_PIN}    0
    Sleep              1s

    Execute Command    gpio write ${GPIO_PIN} 1
    Verifica Stato GPIO    ${GPIO_PIN}    1
    Sleep              1s

    Execute Command    gpio write ${GPIO_PIN} 0
    Verifica Stato GPIO    ${GPIO_PIN}    0
    Sleep              5s


*** Keywords ***
Verifica Stato GPIO
    [Arguments]    ${GPIO_PIN}    ${expected}
    ${state}=    Execute Command    gpio read ${GPIO_PIN}    return_stdout=True
    Log To Console    GPIO Pin Value is: '${state.strip()}'\n
    Should Be Equal    ${state}    ${expected}
    Sleep    1s

Open SSH Session
    Open Connection       ${HOST}
    Login                 ${USERNAME}    ${PASSWORD}
