
enum RGBFormat {
    rgb8 = 0,
    rgbw8,
    rgb16,
    rgbw16
};

enum SwizzleComponent {
    R = 0,
    G,
    B,
    W
};

export class Settings {    
    static fromJSON(json:string):Settings {
        return Object.assign(new Settings(), json);
    }

    toJSON():string {
        return JSON.stringify(this);
    }

    public inFormat: RGBFormat = RGBFormat.rgb8;

    public outConvert: boolean = false;
    public outFormat: RGBFormat = RGBFormat.rgb8;

    public skip: boolean = false;
    public skipN: number = 0;

    public swizzle: boolean = false;
    public swizzle0: SwizzleComponent = SwizzleComponent.R;
    public swizzle1: SwizzleComponent = SwizzleComponent.G;
    public swizzle2: SwizzleComponent = SwizzleComponent.B;
    public swizzle3: SwizzleComponent = SwizzleComponent.W;

    public watchdog: boolean = false;
    public watchdogTimeout: number = 1;
    public watchdogColor: number = 0x000000;
};
