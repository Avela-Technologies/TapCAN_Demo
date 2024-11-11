#ifndef _LGFX_SPI_H
#define _LGFX_SPI_H

class LGFX : public lgfx::LGFX_Device
{
lgfx::Panel_ILI9488     _panel_instance;

public: 
lgfx::Bus_SPI       _bus_instance;  
  LGFX(void)
  {    
    { 
      auto cfg = _bus_instance.config();    // バス設定用の構造体を取得します。

      cfg.spi_host = VSPI_HOST;     // 使用するSPIを選択  (VSPI_HOST or HSPI_HOST)
      cfg.spi_mode = 0;             // SPI通信モードを設定 (0 ~ 3)
      cfg.freq_write = 60000000;    // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)
      cfg.freq_read  = 16000000;    // 受信時のSPIクロック
      cfg.spi_3wire  = true;        // 受信をMOSIピンで行う場合はtrueを設定
      cfg.use_lock   = true;        // トランザクションロックを使用する場合はtrueを設定
      cfg.dma_channel = 1;          // Set the DMA channel (1 or 2. 0=disable)   使用するDMAチャンネルを設定 (0=DMA不使用)
      cfg.pin_sclk = 5;            // SPIのSCLKピン番号を設定
      cfg.pin_mosi = 18;            // SPIのMOSIピン番号を設定
      cfg.pin_miso = 19;            // SPIのMISOピン番号を設定 (-1 = disable)      
      cfg.pin_dc   = 22;            // SPIのD/Cピン番号を設定  (-1 = disable)

      _bus_instance.config(cfg);    // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。      
    }

    { 
      auto cfg1 = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。

      cfg1.pin_cs           =    13;  // CSが接続されているピン番号   (-1 = disable)
      cfg1.pin_rst          =    -1;  // RSTが接続されているピン番号  (-1 = disable)
      cfg1.pin_busy         =    -1;  // BUSYが接続されているピン番号 (-1 = disable)

      cfg1.memory_width     =   320;  // ドライバICがサポートしている最大の幅
      cfg1.memory_height    =   480;  // ドライバICがサポートしている最大の高さ
      cfg1.panel_width      =   320;  // 実際に表示可能な幅
      cfg1.panel_height     =   480;  // 実際に表示可能な高さ
      cfg1.offset_x         =     0;  // パネルのX方向オフセット量
      cfg1.offset_y         =     0;  // パネルのY方向オフセット量
      cfg1.offset_rotation  =     0;  // 回転方向の値のオフセット 0~7 (4~7は上下反転)
      cfg1.dummy_read_pixel =     8;  // ピクセル読出し前のダミーリードのビット数
      cfg1.dummy_read_bits  =     1;  // ピクセル以外のデータ読出し前のダミーリードのビット数
      cfg1.readable         =  false;  // データ読出しが可能な場合 trueに設定
      cfg1.invert           =  false;  // パネルの明暗が反転してしまう場合 trueに設定
      cfg1.rgb_order        = false;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
      cfg1.dlen_16bit       = false;  // データ長を16bit単位で送信するパネルの場合 trueに設定
      cfg1.bus_shared       =  false;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

      _panel_instance.config(cfg1);
    }

   //  { // タッチスクリーン制御の設定を行います。（必要なければ削除）
   //   auto cfg2 = _touch_instance.config();

   //   cfg2.x_min      = 0;    // タッチスクリーンから得られる最小のX値(生の値)
   //   cfg2.x_max      = 319;  // タッチスクリーンから得られる最大のX値(生の値)
   //   cfg2.y_min      = 0;    // タッチスクリーンから得られる最小のY値(生の値)
   //   cfg2.y_max      = 479;  // タッチスクリーンから得られる最大のY値(生の値)
      //cfg.pin_int    = 38;   // INTが接続されているピン番号
   //   cfg2.bus_shared = true; // 画面と共通のバスを使用している場合 trueを設定
   //   cfg2.offset_rotation = 0;// 表示とタッチの向きのが一致しない場合の調整 0~7の値で設定

// I2C接続の場合
  //    cfg2.i2c_port = 0;      // 使用するI2Cを選択 (0 or 1)
  //    cfg2.i2c_addr = 0x38;   // I2Cデバイスアドレス番号
  //    cfg2.pin_sda  = 23;     // SDAが接続されているピン番号
  //    cfg2.pin_scl  = 22;     // SCLが接続されているピン番号
  //    cfg2.freq = 400000;     // I2Cクロックを設定

  //    _touch_instance.config(cfg2);
  //    _panel_instance.setTouch(&_touch_instance);  // タッチスクリーンをパネルにセットします。
  //  }
    setPanel(&_panel_instance); // 使用するパネルをセットします。
  }
};

// File to contain common display functions
extern LGFX lcd;


#endif
