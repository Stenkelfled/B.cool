/**
 * \file
 * 
 * \brief Generate concatenated macros for pretty use of Atmel-Macros
 */

/**
 * \ingroup utils_group
 * \defgroup macro_gen_group Macro Generation
 * \brief Extending the Macros supported by Atmel
 * 
 * It started with ONE problem: Atmel supports nice macros to write readable
 * code when defining the bit masks for the microcontroller's registers - great.
 * Atmel also supports macros to get easy access to these registers - excellent.
 * But unfortunately these macros sometimes contain the names of peripherals. 
 * This results in peripheral-dependent code. If you need to change the peripheral
 * (and i did to do so) it's a mess to change all the macros and you really have
 * to worry about forgetting something. \n
 * <b>Solution:</b>wrapping the Atmel-macros with own ones. These are defined
 * here. Through defining we need to consider the evaluation done by the 
 * Preprocessor. In the <a href="https://gcc.gnu.org/onlinedocs/cpp/Macros.html#Macros">Gcc-Manual</a>
 * is written, that identifiers in a concatenation environment (##) are not expanded. \n
 * <i>Example:</i> 
 * \code {.h}
 * #define CONCAT_PASTER(insert)	foo_ ## insert ## _bar 
 * \endcode
 * <i> will be evaluates as: foo_insert_bar</i>\n    
 * Therefore a second macro is needed, that inserts the real value in the 
 * concatenated statement.\n
 * <i>Example:</i> 
 * \code {.h}   
 * #define CONCAT CONCAT_PASTER(value) 
 * \endcode
 * <i>will be evaluated as foo_value_bar</i> \n
 * If you want to define 'value' in another macro, you will need a third level:
 * \code {.h}
 * #define CONCAT_PASTER(insert)	foo_ ## insert ## _bar
 * #define CONCAT_EVAL(insert)		CONCAT_PASTER(insert)
 * #define CONCAT(insert)			CONCAT_EVAL(insert)
 * 
 * #define MY_VALUE				value
 * \endcode
 * <i>If you now use CONCAT(MY_VALUE), you will get foo_value_bar</i>
 * 
 * Because this is very useful, it is not only used for Atmel-macros, but also
 * for example in the motor definition motor.h 
 * 
 * Please note, that the _EVAl and _PASTER macros are hidden from documentation
 * for better readability, but they are in the code.   
 *
 */ 


#ifndef MACRO_GENERATION_H_
#define MACRO_GENERATION_H_

/**
 * \addtogroup macro_gen_group
 *@{
 */

/** 
 * \name Macros for PIN and PORT (and other register) settings
 * @{
 */
//! \cond
#define _REG(reg,n)		reg##n
//!\endcond
//! concatenates a seperated register. reg = portname,number
#define REG(reg)		_REG(reg)

//! \cond
#define _ADC_REG(idx)	ADC ## idx //!<\internal
//!\endcond
#define ADC_REG(idx)	_ADC_REG(idx) //!< generates a macro for accessing the ADC

//! \cond
#define _ADC_CH(num)	CH ## num //!<\internal
//!\endcond
#define ADC_CH(num)		_ADC_CH(num) //!< generates a macro for accessing an ADC channel

//! \cond
#define _UART_REG(reg,n)	USART ## reg ## n
//! \endcond
//! \brief Generates a macro for accessing an UART. reg = portname,number
#define UART_REG(reg)		_UART_REG(reg)

//! \cond
#define _PORT_(i)		PORT ## i //!<\internal
//!\endcond
#define PORT_(i)		_PORT_(i) //!< generates a macro for access to a port

//! \cond
#define _FIRST(f,s)		f
#define FIRST(foo)		_FIRST(foo)
//! \encond
//! \cond
#define _SECOND(f,s)	s
#define SECOND(foo)		_SECOND(foo)
//! \endcond
//! \cond
#define _STRING(x)		#x
#define STRING(x)		_STRING(x)
//! \endcond
//@}

//!< wrap level for interrupts
#define PMIC_xLVLEN_bm(lvl)		( 1<<(lvl-1) )

//! \cond
#define port_INTn_vect_PASTER(port,num)   PORT ## port ## _INT ## num ## _vect //!<\internal
#define port_INTn_vect_EVAL(port,num)     port_INTn_vect_PASTER(port,num) //!<\internal
//!\endcond
//! generates a macro for pin-change interrupt vector
#define port_INTn_vect(port,num)          port_INTn_vect_EVAL(port,num)

#define PORTn_DIRSET_PASTER(port)          PORT ## port ## _DIRSET
#define PORTn_DIRSET_EVAL(port)            PORTn_DIRSET_PASTER(port)
#define PORTn_DIRSET(port)                 PORTn_DIRSET_EVAL(port)

#define PORTn_DIRCLR_PASTER(port)          PORT ## port ## _DIRCLR
#define PORTn_DIRCLR_EVAL(port)            PORTn_DIRCLR_PASTER(port)
#define PORTn_DIRCLR(port)                 PORTn_DIRCLR_EVAL(port)

#define PORTn_OUTSET_PASTER(port)          PORT ## port ## _OUTSET
#define PORTn_OUTSET_EVAL(port)            PORTn_OUTSET_PASTER(port)
#define PORTn_OUTSET(port)                 PORTn_OUTSET_EVAL(port)

#define PORTn_OUTCLR_PASTER(port)          PORT ## port ## _OUTCLR
#define PORTn_OUTCLR_EVAL(port)            PORTn_OUTCLR_PASTER(port)
#define PORTn_OUTCLR(port)                 PORTn_OUTCLR_EVAL(port)

#define PORTn_func_PASTER(port,func)       PORT ## port ## _ ## func
#define PORTn_func_EVAL(port,func)         PORTn_func_PASTER(port,func)
#define PORTn_func(port,func)              PORTn_func_EVAL(port,func)

#define PINnCTRL_PASTER(pin)               PIN ## pin ## CTRL
#define PINnCTRL_EVAL(pin)                 PINnCTRL_PASTER(pin)
#define PINnCTRL(pin)                      PINnCTRL_EVAL(pin)

/**
 * \name Macros for Event System settings
 *@{
 */
//! \cond
#define EVENT_CHnMUX_PASTER(chan_num)			CH ## chan_num ## MUX //!<\internal
#define EVENT_CHnMUX_EVAL(chan_num)				EVENT_CHnMUX_PASTER(chan_num) //!<\internal
//!\endcond
//! generates a macro for access to the MUX for a specific event channel
#define EVENT_CHnMUX(chan_num)					EVENT_CHnMUX_EVAL(chan_num)

//! \cond
#define EVENT_CHMUX_timer_OVF_PASTER(timer,num)	EVSYS_CHMUX_ ## timer ## num ## _OVF_gc //!<\internal
#define EVENT_CHMUX_timer_OVF_EVAL(timer,num)	EVENT_CHMUX_timer_OVF_PASTER(timer,num) //!<\internal
//!\endcond
//! generates a macro to define the overflow-event of a specific timer as input for event channel multiplexer
#define EVENT_CHMUX_timer_OVF(timer_name)		EVENT_CHMUX_timer_OVF_EVAL(timer_name)

//! \cond
#define EVENT_CHMUX_adc_CHn_PASTER(idx,num)		EVSYS_CHMUX_ADC ## idx ## _CH ## num ## _gc //!<\internal
#define EVENT_CHMUX_adc_CHn_EVAL(idx,num)		EVENT_CHMUX_adc_CHn_PASTER(idx,num) //!<\internal
//!\endcond
//! generates a macro to define the adc-ready-event as input for event channel multiplexer
#define EVENT_CHMUX_adc_CHn(idx,num)			EVENT_CHMUX_adc_CHn_EVAL(idx,num)

//! \cond
#define EVENT_CHMUX_PORTx_PINn_PASTER(port,pin)	EVSYS_CHMUX_PORT ## port ## _PIN ## pin ## _gc //!<\internal
#define EVENT_CHMUX_PORTx_PINn_EVAL(port,pin)	EVENT_CHMUX_PORTx_PINn_PASTER(port,pin) //!<\internal
//!\endcond
//! generates a macro to define the pin-change of a port as input for event channel multiplexer
#define EVENT_CHMUX_PORTx_PINn(port,pin)		EVENT_CHMUX_PORTx_PINn_EVAL(port,pin)

//! \cond
#define EVENT_CHnCTRL_PASTER(ch)				CH ## ch ## C ## TRL //!<\internal
#define EVENT_CHnCTRL_EVAL(ch)					EVENT_CHnCTRL_PASTER(ch) //!<\internal
//!\endcond
//! generates a macro for access to the CTRL register of a specific event channel
#define EVENT_CHnCTRL(ch)						EVENT_CHnCTRL_EVAL(ch)
//@}

/**
 * \name Macros for timer settings
 * @{
 */
//! \cond
#define TC_CLKSEL_EVCHn_PASTER(chan_num)		TC_CLKSEL_EVCH ## chan_num ## _gc //!<\internal
#define TC_CLKSEL_EVCHn_EVAL(chan_num)			TC_CLKSEL_EVCHn_PASTER(chan_num) //!<\internal
//!\endcond
//! generates a macro to select an event channel as clock source for a timer
#define TC_CLKSEL_EVCHn(chan_num)				TC_CLKSEL_EVCHn_EVAL(chan_num)

//! \cond
#define TC_CLKSEL_DIVn_gc_PASTER(prescaler)		TC_CLKSEL_DIV ## prescaler ## _gc
#define TC_CLKSEL_DIVn_gc_EVAL(prescaler)		TC_CLKSEL_DIVn_gc_PASTER(prescaler)
//! \endcond
#define TC_CLKSEL_DIVn_gc(prescaler)			TC_CLKSEL_DIVn_gc_EVAL(prescaler)

//! \cond
#define	TC_EVSEL_CHn_PASTER(chan_num)			TC_EVSEL_CH ## chan_num ## _gc //!<\internal
#define TC_EVSEL_CHn_EVAL(chan_num)				TC_EVSEL_CHn_PASTER(chan_num) //!<\internal
//! \endcond
//! generates a macro for quadrature decoder settings
#define TC_EVSEL_CHn(chan_num)					TC_EVSEL_CHn_EVAL(chan_num)

//! \cond
#define TCn_CCAEN_bm_PASTER(timer_num)			TC ## timer_num ## _CCAEN_bm
#define TCn_CCAEN_bm_EVAL(timer_num)			TCn_CCAEN_bm_PASTER(timer_num)
//! \endcond
#define TCn_CCAEN_bm(timer_num)					TCn_CCAEN_bm_EVAL(timer_num)
//@}

/**
 * \name Macros for ADC settings
 * @{
 */
//! \cond
#define ADC_CH_MUXPOS_PINn_PASTER(pin_num)		ADC_CH_MUXPOS_PIN ## pin_num ## _gc //!<\internal
#define ADC_CH_MUXPOS_PINn_EVAL(pin_num)		ADC_CH_MUXPOS_PINn_PASTER(pin_num) //!<\internal
//!\endcond
//! generates a macro to set the ADC-MUX
#define ADC_CH_MUXPOS_PINn(pin_num)				ADC_CH_MUXPOS_PINn_EVAL(pin_num)

//!\cond
#define ADC_CH_GAIN_nX_gc_PASTER(adc_gain)		ADC_CH_GAIN_ ## adc_gain ## X_gc
#define ADC_CH_GAIN_nX_gc_EVAL(adc_gain)		ADC_CH_GAIN_nX_gc_PASTER(adc_gain)
//!\endcond
//! \brief generates a macro to set ADC gain
#define ADC_CH_GAIN_nX_gc(adc_gain)				ADC_CH_GAIN_nX_gc_EVAL(adc_gain)
//@}

/**
 * \name Interrupt vectors
 *@{
 */ 
//! \cond
#define timer_OVF_vect_PASTER(timer,num)		timer ## num ## _OVF_vect //!<\internal
#define timer_OVF_vect_EVAL(timer,num)			timer_OVF_vect_PASTER(timer,num) //!<\internal
//!\endcond
//! generates a macro for timer-overflow interrupt vector
#define timer_OVF_vect(timer_name)				timer_OVF_vect_EVAL(timer_name)

//! \cond
#define timer_CCx_vect_PASTER(timer,num,cc)		timer ## num ## _CC ## cc ## _vect
#define timer_CCx_vect_EVAL(timer,num,cc)		timer_CCx_vect_PASTER(timer,num,cc)
//! \endcond
//! \brief generates a macro for timer-comare and capture interrupt vector
#define timer_CCx_vect(timer_name,cc)			timer_CCx_vect_EVAL(timer_name,cc)

//! \cond
#define ADCx_CHn_vect_PASTER(adc_idx,ch_num)	ADC ## adc_idx ## _CH ## ch_num ## _vect //!<\internal
#define ADCx_CHn_vect_EVAL(adc_idx,ch_num)		ADCx_CHn_vect_PASTER(adc_idx,ch_num) //!<\internal
//!\endcond
//! generates a macro for adc-channel-ready interrupt vector
#define ADCx_CHn_vect(adc_idx,ch_num)			ADCx_CHn_vect_EVAL(adc_idx,ch_num)

//! \cond
#define port_INTn_vect_PASTER(port,num)			PORT ## port ## _INT ## num ## _vect //!<\internal
#define port_INTn_vect_EVAL(port,num)			port_INTn_vect_PASTER(port,num) //!<\internal
//!\endcond
//! generates a macro for pin-change interrupt vector
#define port_INTn_vect(port,num)				port_INTn_vect_EVAL(port,num)
//@}

//! \name Macros for uart
//@{
//! \cond
#define UART_BAUD_SETTING_xBD_yMHz_PASTER(baud,fper)	UART_BAUD_SETTING_ ## baud ## BD_ ## fper ##MHz
#define UART_BAUD_SETTING_xBD_yMHz_EVAL(baud,fper)		UART_BAUD_SETTING_xBD_yMHz_PASTER(baud,fper)
//! \endond
#define UART_BAUD_SETTING_xBD_yMHz(baud,fper)			UART_BAUD_SETTING_xBD_yMHz_EVAL(baud,fper)

//! \cond
#define UART_TX_PIN_PASTER(port,num)	(1<< (3+4*num) )
#define UART_TX_PIN_EVAL(port,num)		UART_TX_PIN_PASTER(port,num)
//! \endond
#define UART_TX_PIN(port)				UART_TX_PIN_EVAL(port)

//! \cond
#define UART_RX_PIN_PASTER(port,num)	(1<< (2+4*num) )
#define UART_RX_PIN_EVAL(port,num)		UART_RX_PIN_PASTER(port,num)
//! \endond
#define UART_RX_PIN(port)				UART_RX_PIN_EVAL(port)

//! \cond
#define USARTn_type_vect_PASTER(port,num,typ)	USART ## port ## num ## _ ## typ ## _vect
#define USARTn_type_vect_EVAL(port,num,typ)		USARTn_type_vect_PASTER(port,num,typ)
//! \endcond
#define USARTn_type_vect(port,typ)				USARTn_type_vect_EVAL(port,typ)

//@}

//! \name Macros for dma
//@{
//! \cond
#define DMA_CHn_reg_PASTER(ch,reg)		DMA_CH ##ch## _ ##reg
#define DMA_CHn_reg_EVAL(ch,reg)		DMA_CHn_reg_PASTER(ch,reg)
//! \endcond
#define DMA_CHn_reg(ch,reg)				DMA_CHn_reg_EVAL(ch,reg)

//! \cond
#define DMA_CH_TRIGSRC_USARTn_reg_gc_PASTER(port,num,typ)	DMA_CH_TRIGSRC_USART ## port ## num ## _ ## typ ## _gc
#define DMA_CH_TRIGSRC_USARTn_reg_gc_EVAL(port,num,typ)		DMA_CH_TRIGSRC_USARTn_reg_gc_PASTER(port,num,typ)
//! \endcond
#define DMA_CH_TRIGSRC_USARTn_reg_gc(port,typ)		DMA_CH_TRIGSRC_USARTn_reg_gc_EVAL(port,typ)

//! \cond
#define DMA_CHn_vect_PASTER(ch)		DMA_CH ## ch ## _vect
#define DMA_CHn_vect_EVAL(ch)		DMA_CHn_vect_PASTER(ch)
//! \endcond
#define DMA_CHn_vect(ch)			DMA_CHn_vect_EVAL(ch)

//@}

//end of macro_gen_group
//@}

#endif /* MACRO_GENERATION_H_ */
