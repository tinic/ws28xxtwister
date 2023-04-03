import { createApp } from 'vue'
import './style.css'
import App from './App.vue'

import PrimeVue from 'primevue/config'  // import PrimeVue

// import CSS resources
import 'primevue/resources/primevue.min.css'            // core 
import 'primevue/resources/themes/saga-blue/theme.css'  // theme
import 'primeicons/primeicons.css'                      // icons
import '/node_modules/primeflex/primeflex.css'          // PrimeFlex

import Button from 'primevue/button'
import Card from 'primevue/card';
import ColorPicker from 'primevue/colorpicker';
import InputNumber from 'primevue/inputnumber';
import InputSwitch from 'primevue/inputswitch';
import InputText from 'primevue/inputtext';
import Panel from 'primevue/panel'
import SelectButton from 'primevue/selectbutton';
import ScrollPanel from 'primevue/scrollpanel';
import Toolbar from 'primevue/toolbar'

const app = createApp(App)

app.use(PrimeVue)

app.component('Button', Button)
app.component('Card', Card)
app.component('ColorPicker', ColorPicker)
app.component('InputNumber', InputNumber)
app.component('InputSwitch', InputSwitch)
app.component('InputText', InputText)
app.component('Panel', Panel)
app.component('SelectButton', SelectButton)
app.component('ScrollPanel', ScrollPanel)
app.component('Toolbar', Toolbar)

app.mount('#app')
