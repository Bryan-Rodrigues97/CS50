// After load all elements from DOM
document.addEventListener('DOMContentLoaded', () => {
    handleSlider()
    handlePwdGenerate();
});

function handleSlider(){
    // Slider
    const slider = document.getElementById('pwdSliderLen')
    const output = document.getElementById('pwdLength')

    slider.oninput = function() {
        output.innerHTML = this.value
    }
}

function generatePwd(){
    const upper = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    const lower = 'abcdefghijklmnopqrstuvwxyz'
    const numbers = '0123456789'
    const symbols = '!@#$%^&*()_+[]{}|;:,.<>?/~`'

    const useLower = document.getElementById('upperCase').checked
    const useUpper = document.getElementById('lowerCase').checked
    const useNumbers = document.getElementById('numbers').checked
    const useSymbols = document.getElementById('symbols').checked

    let pwdPattern = ''
    pwdPattern = useLower ? lower : ''
    pwdPattern += useUpper ? upper : ''
    pwdPattern += useNumbers ? numbers : ''
    pwdPattern += useSymbols ? symbols : ''

    if (pwdPattern){
        shuffle(pwdPattern)
    }
    else{
        alert("At least one checkbox must be selected")
    }
}

function shuffle(pattern) {
    let array = pattern.split('');
    for (let i = array.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));

        const tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    let pwd = ''
    for(let i = 0; i < document.getElementById('pwdSliderLen').value ; i++){
        const j = Math.floor(Math.random() * array.length);
        pwd += array[j]
    }

    document.getElementById('password').innerHTML = pwd
}


function handlePwdGenerate(){
    // Button Click
    const btn = document.querySelector('button');
    btn.onclick = (event) => {
        generatePwd()
        event.preventDefault()
    }
}

