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
import Dropdown from 'primevue/dropdown';
import InputNumber from 'primevue/inputnumber';
import InputSwitch from 'primevue/inputswitch';
import Panel from 'primevue/panel'
import SelectButton from 'primevue/selectbutton';
import ScrollPanel from 'primevue/scrollpanel';
import Toolbar from 'primevue/toolbar'

const app = createApp(App)

app.use(PrimeVue)

app.component('Button', Button)
app.component('Dropdown', Dropdown)
app.component('InputNumber', InputNumber)
app.component('InputSwitch', InputSwitch)
app.component('Panel', Panel)
app.component('SelectButton', SelectButton)
app.component('ScrollPanel', ScrollPanel)
app.component('Toolbar', Toolbar)

app.mount('#app')
