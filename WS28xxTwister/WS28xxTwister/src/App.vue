<script setup lang="ts">

import { ref, computed } from 'vue';

const rgbInValue = ref('RGB 8bit');
const rgbInOptions = ref(['RGB 8bit', 'RGBW 8bit', 'RGB 16bit', 'RGBW 16bit']);

const rgbOutChecked = ref(false);
const rgbOutValue = ref('RGB 8bit');
const rgbOutOptions = ref(['RGB 8bit', 'RGBW 8bit', 'RGB 16bit', 'RGBW 16bit']);

const skipLEDChecked = ref(false);
const skipLEDValue = ref(0);

const swizzleLEDComponentsChecked = ref(false);
const swizzle1Select = ref('R');
const swizzle2Select = ref('G');
const swizzle3Select = ref('B');
const swizzle4Select = ref('W');
const swizzleOptionsRGBW = ref(['R', 'G', 'B', 'W']);
const swizzleOptionsRGB = ref(['R', 'G', 'B']);

const watchDogChecked = ref(false);
const watchDogColor = ref('FFFFFF');
const watchDogTimeout = ref(1);

const showRGBWSwizzle = computed(() => rgbInValue.value == 'RGBW 8bit' || 
                                       rgbInValue.value == 'RGBW 16bit');

const connectedToDevice = ref(false);

</script>

<template>
  <div class="header">
    <img src="./assets/logo.png" class="logo"/>
    <h3>WS28xx Twister</h3>
  </div>
  <div class="settings">
    <ScrollPanel class="scrollpanel scrollbar">
      <Panel header="Input LED data format" class="panel">
        <div>
          <SelectButton v-model="rgbInValue" :options="rgbInOptions" aria-labelledby="basic" />
        </div>
      </Panel>
      <Panel header="Convert to" :collapsed="!rgbOutChecked" class="panel">
        <template #icons>
          <InputSwitch v-model="rgbOutChecked" />
        </template>
        <div>
          <SelectButton v-model="rgbOutValue" :options="rgbOutOptions" aria-labelledby="basic" />
        </div>
      </Panel>
      <Panel header="Skip LED data" :collapsed="!skipLEDChecked" class="panel">
        <template #icons>
          <InputSwitch v-model="skipLEDChecked" />
        </template>
        <div class="flex flex-column align-items-center gap-3">
          <div class="p-inputgroup w-full md:w-20rem">
            <span class="p-inputgroup-addon">Number of LEDs to skip</span>
            <InputNumber v-model="skipLEDValue" inputId="minmax" :min="0" :max="9999" />
          </div>
        </div>
      </Panel>
      <Panel header="Swizzle input LED colors" :collapsed="!swizzleLEDComponentsChecked" class="panel">
        <template #icons>
          <InputSwitch v-model="swizzleLEDComponentsChecked" />
        </template>
        <div v-if="showRGBWSwizzle" class="flex-auto">
          <SelectButton v-model="swizzle1Select" :options="swizzleOptionsRGBW" aria-labelledby="basic" />
          <SelectButton v-model="swizzle2Select" :options="swizzleOptionsRGBW" aria-labelledby="basic" />
          <SelectButton v-model="swizzle3Select" :options="swizzleOptionsRGBW" aria-labelledby="basic" />
          <SelectButton v-model="swizzle4Select" :options="swizzleOptionsRGBW" aria-labelledby="basic" />
        </div>
        <div v-else class="flex-auto"> 
          <SelectButton v-model="swizzle1Select" :options="swizzleOptionsRGB" aria-labelledby="basic" />
          <SelectButton v-model="swizzle2Select" :options="swizzleOptionsRGB" aria-labelledby="basic" />
          <SelectButton v-model="swizzle3Select" :options="swizzleOptionsRGB" aria-labelledby="basic" />
        </div>
      </Panel>
      <Panel header="Watchdog" :collapsed="!watchDogChecked" class="panel">
        <template #icons>
          <InputSwitch v-model="watchDogChecked" />
        </template>
        <div class="flex flex-column align-items-center gap-3">
          <div class="p-inputgroup w-full md:w-15rem">
            <span class="p-inputgroup-addon">Timeout</span>
            <InputNumber v-model="watchDogTimeout" inputId="minmax" :min="1" :max="9999" />
            <span class="p-inputgroup-addon">s</span>
          </div>
          <ColorPicker v-model="watchDogColor" id="colorPicker" inline />
          <div class="flex align-items-center gap-3">
            <ColorPicker v-model="watchDogColor" id="colorPicker" />
            <InputText v-model="watchDogColor" id="colorInput"></InputText>
          </div>
        </div>
      </Panel>
      <div class="space"/>
    </ScrollPanel>
  </div>
  <Toolbar class="toolbar">
    <template #start>
      <Button label="Read from Device" icon="pi pi-check" class="mr-2" :disabled="!connectedToDevice"/>
      <Button label="Write to Device" icon="pi pi-check" severity="warning" class="mr-2" :disabled="!connectedToDevice"/>
    </template>
    <template #end>
      <Button label="Quit" icon="pi pi-times" severity="danger" class="mr-2"/>
    </template>
  </Toolbar>
</template>

<style scoped>

::v-deep(.p-scrollpanel.scrollbar .p-scrollpanel-wrapper) {
}

::v-deep(.p-scrollpanel.scrollbar .p-scrollpanel-bar) {
    opacity: 1;
    transition: background-color 0.3s;
}

::v-deep(.p-scrollpanel.scrollbar .p-scrollpanel-bar:hover) {
}

.header {
  position: absolute; 
  left: 0;
  top: 0;
  width: 100%;
  align-content: start;
  align-items: center;
  display: flex;
}

.logo {
  float: left;
  height: 6em;
  padding: 1.5em;
  will-change: filter;
  transition: filter 300ms;
}
.logo:hover {
  filter: drop-shadow(0 0 2em #646cffaa);
}
.logo.vue:hover {
  filter: drop-shadow(0 0 2em #42b883aa);
}

.toolbar {
  position: absolute; 
  width: 100%;
  height: 75px;
  left: 0;
  bottom: 0;
  box-shadow: 0px 0px 20px black;
  z-index: 10;
}

.space {
  height: 20px;
}

.scrollpanel {
  position: absolute; 
  left: 10px;
  top: 100px;
  width: calc(100% - 20px);
  height: calc(100% - 100px - 75px);
  padding-top: 0px;
  padding-left: 0px;
  padding-right: 0px;
  padding-bottom: 0px;
}

.panel {
  padding-right: 15px;
}

.settings {
  padding-top: 20px;
  padding-left: 20px;
  padding-right: 20px;
  padding-bottom: 20px;
}

</style>
