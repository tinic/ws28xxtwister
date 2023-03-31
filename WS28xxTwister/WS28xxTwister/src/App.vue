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

const showRGBWSwizzle = computed(() => rgbInValue.value == 'RGBW 8bit' || 
                                       rgbInValue.value == 'RGBW 16bit');

</script>

<template>
  <div class="header">
    <img src="./assets/logo.png" class="logo"/>
    <h3>WS28xx Twister</h3>
  </div>
  <div class="settings">
    <ScrollPanel class="scrollpanel" >
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
        <div class="flex-auto">
          <label for="locale-us" class="font-bold mb-2">Number of LEDs to skip</label>
          <InputNumber v-model="skipLEDValue" inputId="minmax" :min="0" :max="9999" />
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
      </Panel>
      <div class="space"/>
    </ScrollPanel>
  </div>
  <Toolbar class="toolbar">
    <template #start>
      <Button label="Save" icon="pi pi-check" severity="warning" />
    </template>
    <template #end>
      <Button label="Quit" icon="pi pi-times" severity="danger" />
    </template>
  </Toolbar>
</template>

<style scoped>

label {
    padding-right:8px;
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
