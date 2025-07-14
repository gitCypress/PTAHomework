stateDiagram-v2
    [*] --> NoCoin : 机器启动

    NoCoin: 无硬币
    HasCoin: 有硬币
    Dispensing: 出货中 (瞬时)
    SoldOut: 售罄/无效 (瞬时)

    NoCoin --> HasCoin : insertCoin() / 投币
    NoCoin : onEnter: 提示投币

    HasCoin --> NoCoin : ejectCoin() / 退币 (执行退币动作)
    HasCoin : onEnter: 提示选择商品
    HasCoin -- selectItem(有效且有货) --> Dispensing : / 选择商品
    HasCoin -- selectItem(无效或售罄) --> SoldOut : / 选择商品

    Dispensing --> NoCoin : onEnter: 发放商品
    SoldOut --> NoCoin : onEnter: 提示无货/无效, 执行退币

    %% 描述默认行为 (在状态下未定义的操作)
    state NoCoin {
        ejectCoin() : 默认报错
        selectItem() : 默认报错
    }
    state HasCoin {
        insertCoin() : 默认报错
    }
    state Dispensing {
        insertCoin() : 默认报错
        ejectCoin() : 默认报错
        selectItem() : 默认报错
    }
    state SoldOut {
        insertCoin() : 默认报错
        ejectCoin() : 默认报错 (onEnter已处理)
        selectItem() : 默认报错
    }