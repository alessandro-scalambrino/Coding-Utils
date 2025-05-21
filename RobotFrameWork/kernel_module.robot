*** Settings ***
Library    SSHLibrary
Library    Process
Suite Setup     Open SSH Session
Suite Teardown  Close Connection

*** Variables ***
${HOST}           None
${USERNAME}       None
${PASSWORD}       None
${KO_PATH}        None
${MODULE_NAME}    None

*** Test Cases ***
Insert Module
    ${stdout}    ${stderr}    ${rc}=    Execute Command    sh -c "echo ${PASSWORD} | sudo -S /usr/sbin/insmod ${KO_PATH}"    return_stderr=True    return_rc=True
    Run Keyword If    ${rc} != 0    Fail    Failed to insert module\nReturn code: ${rc}\nError message: ${stderr}

Is Loaded
    ${output}=    Execute Command    lsmod
    Should Contain    ${output}    ${MODULE_NAME}

Remove Module
    ${stdout}    ${stderr}    ${rc}=    Execute Command    sh -c "echo ${PASSWORD} | sudo -S /usr/sbin/rmmod ${KO_PATH}"    return_stderr=True    return_rc=True
    Run Keyword If    ${rc} != 0    Fail    Failed to remove module\nReturn code: ${rc}\nError message: ${stderr}

Is Removed
    ${output}=    Execute Command    lsmod
    Should Not Contain    ${output}    ${MODULE_NAME}

*** Keywords ***
Open SSH Session
    Open Connection       ${HOST}
    Login                 ${USERNAME}    ${PASSWORD}
